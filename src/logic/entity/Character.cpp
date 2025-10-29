#include "Character.h"
#include "../utils/Camera.h"
#include "../utils/Stopwatch.h"
#include "../utils/Utils.h"
#include "../utils/Vector.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>

using namespace Config;

Character::Character(NodePtr node, float width, float height)
    : Entity(width, height), current_node_(std::move(node)) {
  target_node_ = nullptr;
  setPosition(current_node_->getPosition());
}

void Character::update() {
  if (!target_node_)
    stop();
  else
    move();
  if (overshotTarget()) {
    takeTarget();
    updateTarget(direction_);
  }
  notifyObservers();
}

Direction Character::getTargetDirection() const {
  if (!target_node_)
    throw std::logic_error("can't get targetDirection since target is absent");
  if (target_node_->row_ == current_node_->row_) {
    if (target_node_->column_ > current_node_->column_)
      return Direction::RIGHT;
    return Direction::LEFT;
  }
  if (target_node_->column_ == current_node_->column_) {
    if (target_node_->row_ > current_node_->row_)
      return Direction::DOWN;
    return Direction::UP;
  }
  throw std::logic_error(
      "current node and target node are not on the same line");
}

void Character::move() {
  if (!moving_)
    return;
  float delta = Stopwatch::getInstance()->getDeltaTime();
  float speed = speed_ * delta;
  MyVector new_pos = Camera::world2Window(position_);
  Direction direction;
  try {
    direction = getTargetDirection();
  } catch (std::logic_error &e) {
    std::cout << e.what() << std::endl;
  }
  if (direction == Direction::LEFT) {
    new_pos.x -= speed;
  }
  if (direction == Direction::RIGHT) {
    new_pos.x += speed;
  }
  if (direction == Direction::UP) {
    new_pos.y -= speed;
  }
  if (direction == Direction::DOWN) {
    new_pos.y += speed;
  }
  position_ = Camera::window2World(new_pos);
}

bool Character::overshotTarget() const {
  if (!target_node_)
    return false;
  MyVector prev_pos = current_node_->getPosition();
  MyVector target_pos = target_node_->getPosition();

  Vector vec1{prev_pos, target_pos};
  Vector vec2{prev_pos, position_};

  float node_2_target = std::pow(vec1.getMagnitude(), 2);
  float node_2_self = std::pow(vec2.getMagnitude(), 2);

  return node_2_self > node_2_target;
}

void Character::takeTarget() {
  current_node_ = target_node_;
  target_node_ = nullptr;
  setPosition(current_node_->getPosition());
}

void Character::setTarget(NodePtr target) { target_node_ = std::move(target); }

bool Character::updateTarget(Direction direction) {
  // Returns true if the target changed.

  auto maze = Maze::getInstance();

  // First, try finding a target
  if (!target_node_) {
    setTarget(maze->findNeighbor(current_node_->row_, current_node_->column_,
                                 direction));
    if (target_node_) {
      updateDirection(direction);
      return true;
    } else if (!target_node_) {
      return false;
    }
  }
  NodePtr new_target =
      maze->findNeighbor(target_node_->row_, target_node_->column_, direction);
  if (!new_target)
    return false;
  if (new_target && new_target == current_node_)
    reverseDirection();
  if (new_target && new_target == target_node_)
    return false; // Target didn't change
  if (direction == direction_)
    // To avoid unnecessary update calls if direction didn't change
    return false;

  // only set (the next) direction, wait for pacman to reach previous target
  setDirection(direction);
  return true;
}

bool Character::findAnyTarget() {
  if (updateTarget(Direction::RIGHT))
    ;
  else if (updateTarget(Direction::LEFT))
    ;
  else if (updateTarget(Direction::DOWN))
    ;
  else if (updateTarget(Direction::UP))
    ;
  else
    throw std::logic_error("Character has no direction to go");
};

void Character::stop() { moving_ = false; }
void Character::startMove() { moving_ = true; }
void Character::reverseDirection() {
  if (!target_node_)
    throw std::logic_error("Can't reverse when target is absent");
  if (direction_ != getTargetDirection())
    setDirection(getTargetDirection());
  swap(target_node_, current_node_);
  updateDirection(Utils::getReverseDirection(direction_));
}

void Character::setDirection(Direction direction) { direction_ = direction; }

std::vector<Direction> Character::getPossibleDirections(NodePtr *node) const {

  std::vector<Direction> result = {};
  std::array<Direction, 4> directions = {Direction::UP, Direction::DOWN,
                                         Direction::LEFT, Direction::RIGHT};

  for (auto &d : directions) {
    if (Maze::getInstance()->findNeighbor(node->get()->row_,
                                          node->get()->column_, d))
      result.push_back(d);
  }
  return result;
}
void Character::updateDirection(Direction direction) {
  // todo: get rid of Direction::NONE
  // and use std::optional instead
  setDirection(direction);
  auto state = state_;

  switch (direction) {
  case Direction::NONE:
    break;
  case Direction::LEFT:
    state = Entity::State::LEFT;
    break;
  case Direction::RIGHT:
    state = Entity::State::RIGHT;
    break;
  case Direction::UP:
    state = Entity::State::UP;
    break;
  case Direction::DOWN:
    state = Entity::State::DOWN;
    break;
  }
  setState(state);
  notifyObservers();
}
