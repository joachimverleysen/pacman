#include "Ghost.h"
#include "../utils/CollisionHandler.h"
#include "../utils/Random.h"
#include "../utils/Vector.h"
#include <cmath>
#include <utility>

Ghost::Ghost(NodePtr node, float width, float height)
    : Character(std::move(node), width, height) {
  speed_ = Config::Ghost::SPEED;
  startMove();
}

void Ghost::onCollision(Entity *other) {
  deactivate();}

EntityType Ghost::getType() const { return EntityType::Ghost; }

bool Ghost::allowsSpawn(Entity *other) {
  return CollisionHandler::checkCollision(this, other);
}

bool Ghost::chooseDirection(const std::vector<Direction> &options) {
  for (auto &direction : options) {
    if (updateTarget(direction))
      return true;
  }
  return false;
}
bool Ghost::chooseDirection() {
  bool disable_reversing{true};
  std::vector<Direction> options =
      Maze::getInstance()->getPossibleDirections(current_node_);
  if (disable_reversing)
    options.erase(std::remove(options.begin(), options.end(),
                              Utils::getReverseDirection(direction_)),
                  options.end());
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
