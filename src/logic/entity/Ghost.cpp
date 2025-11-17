#include "Ghost.h"
#include "../utils/CollisionHandler.h"
#include "../utils/Random.h"
#include "../utils/Vector.h"
#include <cmath>
#include <utility>

Ghost::Ghost(NodePtr node, float width, float height, std::shared_ptr<Player> player, GhostType type)
    : Character(std::move(node), width, height), player_(player), ghost_type_(type) {
  speed_ = Config::Ghost::SPEED;
  startMove();
}


float Ghost::getDistance2Player(Direction direction, float predictive_offset=0) const {
  // Returns Manhattan distance
  // if ghost would take 1 step to <direction>
  MyVector prediction_pos = Utils::positionAfterMove(player_->getPosition(),
                                                     player_->getDirection(),
                                                     predictive_offset);
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

  float x = std::abs(vec.x - prediction_pos.x);
  float y = std::abs(vec.y - prediction_pos.y);
  return x + y;
}

void Ghost::killPlayer() const {
  player_->deactivate();
}

void Ghost::onCollision(Entity *other) {
  if (mode_ == Mode::NORMAL)
    killPlayer();
  else deactivate();
}

EntityType Ghost::getType() const { return EntityType::Ghost; }

bool Ghost::updateTarget(const std::vector<Direction> &options) {
  for (auto &direction : options) {
    if (updateTarget(direction))
      return true;
  }
  return false;
}

Direction Ghost::chooseLockingDirection() {
  if (Random::getInstance()->decide(0.5)) {
    return direction_;
  }
  else
    return chooseRandomDirection(true);
}
Direction Ghost::chooseDirection() {
  if (mode_ == Mode::FRIGHTENED)
    return chooseFleeDirection();
  else  { // Chase Mode
    if (ghost_type_ == GhostType::Orange)
      return chooseLockingDirection();
    if (ghost_type_ == GhostType::Red)
      return chooseChaseDirection(0.1);   // With predictive offset 0.1
    if (ghost_type_ == GhostType::Pink)
      return chooseChaseDirection(0.0);   // No predictive offset
  }

    return chooseRandomDirection(false);
}

Direction Ghost::chooseRandomDirection(bool should_change=false) {
  bool disable_reversing{true};
  std::vector<Direction> options =
      Maze::getInstance()->getPossibleDirections(current_node_);
  if (disable_reversing)
    options.erase(std::remove(options.begin(), options.end(),
                              Utils::getReverseDirection(direction_)),
                  options.end());
  if (should_change)
    options.erase(std::remove(options.begin(), options.end(),
                    direction_),
                  options.end());

  Random::getInstance()->shuffle(options);
  return options[0];
}

Direction Ghost::chooseChaseDirection(float predictive_offset=0) {
  std::vector<Direction> options =
      Maze::getInstance()->getPossibleDirections(current_node_);
  if (reverse_count_ >= max_reversing_) {

    options.erase(std::remove(options.begin(), options.end(),
                              Utils::getReverseDirection(direction_)),
                  options.end());
  }
  Random::getInstance()->shuffle(options);
  Direction chosen = options[0];
  float min = getDistance2Player(chosen, 0);
  for (auto d : options) {
    if (getDistance2Player(d, predictive_offset) < min) {
      min = getDistance2Player(d, predictive_offset);
      chosen = d;
    }
  }
  return chosen;
}

Direction Ghost::chooseFleeDirection() {
  std::vector<Direction> options =
    Maze::getInstance()->getPossibleDirections(current_node_);
  if (reverse_count_ >= max_reversing_) {

    options.erase(std::remove(options.begin(), options.end(),
                              Utils::getReverseDirection(direction_)),
                  options.end());
  }
  Random::getInstance()->shuffle(options);
  Direction chosen = options[0];
  float max_ = getDistance2Player(chosen, 0);
  for (auto d : options) {
    if (getDistance2Player(d, 0) > max_) {
      max_ = getDistance2Player(d, 0);
      chosen = d;
    }
  }
  return chosen;
}


void Player::move(float offset) {
  switch (direction_) {
    case Direction::LEFT:
      position_.x -= offset;
      break;
    case Direction::RIGHT:
      position_.x += offset;
      break;
    case Direction::UP:
      position_.y -= offset;
      break;
    case Direction::DOWN:
      position_.y += offset;
      break;
    case Direction::NONE:
      break;
  }
}


bool Ghost::findAnyTarget() {
  auto direction = chooseRandomDirection();
  return updateTarget(direction);
}

void Ghost::enterFrightenedMode(std::shared_ptr<Timer> timer) {
  mode_= Mode::FRIGHTENED;
  frightened_timer_ = timer;
  reverseDirection();
}

void Ghost::enterChaseMode() {
  state_ = State::IDLE;
  mode_ = Mode::NORMAL;
  reverseDirection();
}

void Ghost::startTimeOut(float seconds) {
  timeout_timer_ = Stopwatch::getInstance()->getNewTimer(seconds);
}

bool Ghost::timeout() const {
  if (!timeout_timer_.lock()) return false;
  if (timeout_timer_.lock()->done()) return false;
  return true;
}

void Ghost::updateMode() {
  if (frightened_timer_ && frightened_timer_->done()) {
    frightened_timer_ = nullptr;
    enterChaseMode();
  }
}

void Ghost::update() {
  updateMode();
  Direction prev = direction_;
  if (!target_node_) {
    auto direction = chooseRandomDirection();
    updateTarget(direction) || findAnyTarget();
  } else if (target_node_ && !timeout())
    move();
  if (overshotTarget()) {
    takeTarget();
    portalCheck();
    auto direction = chooseDirection();
    updateTarget(direction) || findAnyTarget();
  }

  if (Utils::getReverseDirection(prev) == direction_)
    reverse_count_++;
  else if (direction_ != prev) {
    reverse_count_ = 0;
  }
  notifyObservers();

}
