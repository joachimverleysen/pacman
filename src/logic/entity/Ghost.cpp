#include "Ghost.h"
#include "../utils/CollisionHandler.h"
#include "../utils/Vector.h"
#include "../utils/Random.h"
#include <cmath>
#include <utility>

Ghost::Ghost(NodePtr node, float width, float height)
    : Character(std::move(node), width, height) {
  if (updateTarget(Direction::RIGHT))
    startMove();
}

void Ghost::onCollision(Entity *other) {}

EntityType Ghost::getType() const { return EntityType::Ghost; }

bool Ghost::allowsSpawn(Entity *other) {
  return CollisionHandler::checkCollision(this, other);
}

bool Ghost::chooseDirection(std::vector<Direction> options) {
  for (auto& direction: options) {
    if (updateTarget(direction))
      return true;
  }
  return false;
}
bool Ghost::chooseDirection() {
  std::vector<Direction> options = {Direction::LEFT, Direction::RIGHT, Direction::UP, Direction::DOWN};
  options.erase(std::remove(options.begin(), options.end(), Utils::getReverseDirection(direction_)), options.end());
  Random::getInstance()->shuffle(options);
  chooseDirection(options) || findAnyTarget();
  if (!target_node_)
    throw std::logic_error("chooseDirection shouldn't fail");
  return true;
}

void Ghost::update() {
  if (!target_node_)
    chooseDirection();
  else
    move();
  if (overshotTarget()) {
    takeTarget();
    chooseDirection();
  }
  notifyObservers();
}
