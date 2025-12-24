#include "CollisionHandler.h"
#include "Event.h"

bool CollisionHandler::onCollision(Entity *first, Entity *second) {
  first->onCollision(second);
  second->onCollision(first);
  return true;
}

std::shared_ptr<Event> CollisionHandler::checkCollision(const Entity *first,
                                                        const Entity *second) {
  if (!checkCollision(first->getBoundingBox(), second->getBoundingBox(), -0.03))
    return nullptr;

  if (second->getType() == EntityType::Player)
    std::swap(first, second);
  if (first->getType() != EntityType::Player)
    return nullptr;

  if (second->getType() == EntityType::Ghost &&
    second->getCollisionBehavior(EntityType::Player) == CollisionBehavior::KILLING)
    return std::make_shared<PacmanDiesEvent>();

  if (second->getType() == EntityType::Ghost &&
    second->getCollisionBehavior(EntityType::Player) == CollisionBehavior::CONSUMABLE)
    return std::make_shared<GhostEatenEvent>();

  if (second->getType() == EntityType::Coin)
    return std::make_shared<CoinEatenEvent>();

  if (second->getType() == EntityType::Fruit)
    return std::make_shared<FruitEatenEvent>();
  return nullptr;
}

bool CollisionHandler::checkCollision(const Entity *first,
                                      const Entity *second, float margin) {
  return checkCollision(first->getBoundingBox(), second->getBoundingBox(), margin);
}

bool CollisionHandler::checkCollision(const BoundingBox &first,
                                      const BoundingBox &second) {
  if (first.bottom < second.top && first.top > second.bottom &&
      first.left < second.right && first.right > second.left) {
    return true;
  }
  return false;
}


bool CollisionHandler::checkCollision(const BoundingBox &first,
                                      const BoundingBox &second, float margin) {
  BoundingBox a = first;
  BoundingBox b = second;
  a += margin / 2;
  b += margin / 2;
  if (a.bottom < b.top && a.top > b.bottom && a.left < b.right &&
      a.right > b.left) {
    return true;
  }
  return false;
}
