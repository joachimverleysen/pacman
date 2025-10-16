#include "Character.h"
#include "../utils/Camera.h"
#include "../utils/Stopwatch.h"
#include "../utils/Vector.h"
#include <cmath>
#include <iostream>

using namespace Config;

Character::Character(NodePtr node, float width, float height, float scale)
    : Entity(width, height, scale), current_node_(node) {
  auto maze = Maze::getInstance();
  target_node_ = maze->findNeighbor(current_node_->row_, current_node_->column_,
                                    direction_);
  setPosition(current_node_->getPosition());
}

void Character::update() {
  if (!target_node_)
    stop();
  else
    move();
  if (overshotTarget()) {
    setPosition(target_node_->getPosition());
    updateNodes();
    stop();
  }
  notifyObservers();
}

void Character::move() {
  if (!moving_)
    return;
  float delta = Stopwatch::getInstance()->getDeltaTime();
  // std::cout << delta << '\n';
  // todo: Use statistics to replace the magic number
  delta = std::min(delta, 0.104f); // Limit delta to avoid 'jumping'
  float speed = speed_ * delta;
  Position new_pos = Camera::world2Window(position_);

  if (direction_ == Direction::LEFT) {
    new_pos.x -= speed;
  }
  if (direction_ == Direction::RIGHT) {
    new_pos.x += speed;
  }
  if (direction_ == Direction::UP) {
    new_pos.y -= speed;
  }
  if (direction_ == Direction::DOWN) {
    new_pos.y += speed;
  }
  position_ = Camera::window2World(new_pos);
}

bool Character::overshotTarget() const {
  if (!target_node_)
    return false;
  Position prev_pos = current_node_->getPosition();
  Position target_pos = target_node_->getPosition();

  Vector vec1{prev_pos, target_pos};
  Vector vec2{prev_pos, position_};

  float node_2_target = std::pow(vec1.getMagnitude(), 2);
  float node_2_self = std::pow(vec2.getMagnitude(), 2);

  return node_2_self > node_2_target;
}

void Character::updateTarget() {
  auto maze = Maze::getInstance();
  NodePtr new_target;
  new_target = maze->findNeighbor(current_node_->row_, current_node_->column_,
                                  direction_);
  target_node_ = new_target;
}
void Character::updateNodes() {
  auto maze = Maze::getInstance();
  NodePtr new_target;
  new_target = maze->findNeighbor(current_node_->row_, current_node_->column_,
                                  direction_);
  if (target_node_)
    current_node_ = target_node_;
  if (new_target) {
    target_node_ = new_target;
  }
}

void Character::stop() { moving_ = false; }
void Character::startMove() {
  updateTarget();
  moving_ = true;
}
