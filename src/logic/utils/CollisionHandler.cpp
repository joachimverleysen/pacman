#include "CollisionHandler.h"
#include <iostream>

bool CollisionHandler::onCollision(Entity *first, Entity *second) {
  if (checkCollision(first, second)) {
    first->onCollision(second);
    second->onCollision(first);
    return true;
  }
  return false;
}

bool CollisionHandler::checkCollision(const Entity *first,
                                      const Entity *second) {
  return checkCollision(first->getBoundingBox(), second->getBoundingBox());
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
