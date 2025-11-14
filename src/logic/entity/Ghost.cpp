#include "Ghost.h"
#include "../utils/CollisionHandler.h"
#include "../utils/Random.h"
#include "../utils/Vector.h"
#include <cmath>
#include <utility>

Ghost::Ghost(NodePtr node, float width, float height, std::shared_ptr<Player> player)
    : Character(std::move(node), width, height), player_(player) {
  speed_ = Config::Ghost::SPEED;
  startMove();
}

float Ghost::getDistance2Player(Direction direction) const {
  // Returns Manhattan distance
  // if ghost would take 1 step to <direction>
  float step_size{0.1};
  MyVector vec{0, 0};
  switch (direction) {
    case Direction::LEFT:
      vec = {-step_size, 0};
      break;
    case Direction::RIGHT:
      vec = {step_size, 0};
      break;
    case Direction::UP:
      vec = {0, step_size};
      break;
    case Direction::DOWN:
      vec = {0, -step_size};
      break;
    case Direction::NONE:
      throw std::invalid_argument("NONE direction was passed");
  }
  vec = vec + position_;

  float x = std::abs(vec.x - player_->getPosition().x);
  float y = std::abs(vec.y - player_->getPosition().y);
  return x+y;
}

void Ghost::onCollision(Entity *other) {
  deactivate();
  if (mode_ == Mode::CHASE);
//    killPlayer();
}

void Ghost::killPlayer() const {
  player_->deactivate();
}

EntityType Ghost::getType() const { return EntityType::Ghost; }

bool Ghost::updateTarget(const std::vector<Direction> &options) {
  for (auto &direction : options) {
    if (updateTarget(direction))
      return true;
  }
  return false;
}

bool Ghost::chooseDirection() {
  if (mode_ == Mode::FLEE)
    chooseFleeDirection();
  else if (mode_ == Mode::CHASE)
    chooseChaseDirection();
  else
    chooseRandomDirection();

}
bool Ghost::chooseRandomDirection() {
  bool disable_reversing{true};
  std::vector<Direction> options =
      Maze::getInstance()->getPossibleDirections(current_node_);
  if (disable_reversing)
    options.erase(std::remove(options.begin(), options.end(),
                              Utils::getReverseDirection(direction_)),
                  options.end());
  Random::getInstance()->shuffle(options);
  updateTarget(options) || findAnyTarget();
  if (!target_node_)
    throw std::logic_error("chooseRandomDirection shouldn't fail");
  return true;
}

bool Ghost::chooseChaseDirection() {
  std::vector<Direction> options = Maze::getInstance()->getPossibleDirections(current_node_);
  if (reverse_count_ >= max_reversing_) {

    options.erase(std::remove(options.begin(), options.end(),
                              Utils::getReverseDirection(direction_)),
                  options.end());
  }
  Direction chosen = options[0];
  float min = getDistance2Player(chosen);
  for (auto d : options) {
    if (getDistance2Player(d) < min) {
      min = getDistance2Player(d);
      chosen = d;
    }
  }
  if (updateTarget(chosen) || findAnyTarget())
    return true;

  return false;   // shouldn't happen... !!!
}

bool Ghost::chooseFleeDirection() {
  std::vector<Direction> options = Maze::getInstance()->getPossibleDirections(current_node_);
  Direction chosen = options[0];
  float max_ = getDistance2Player(chosen);
  for (auto d : options) {
    if (getDistance2Player(d) > max_) {
      max_ = getDistance2Player(d);
      chosen = d;
    }
  }
  if (updateTarget(chosen) || findAnyTarget())
    return true;

  return false;   // shouldn't happen... !!!
}

void Ghost::update() {
  Direction prev = direction_;
  if (!target_node_) {
    chooseRandomDirection();
  }
  else if (target_node_)
    move();
  if (overshotTarget()) {
    takeTarget();
    portalCheck();
    chooseDirection();
  }

  if (Utils::getReverseDirection(prev) == direction_)
    reverse_count_++;
  else if (direction_ != prev) {
    reverse_count_ = 0;
  }
  notifyObservers();
}
