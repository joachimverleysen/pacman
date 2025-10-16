//
// Created by joachimverleysen on 11/26/24.
//

#include "Player.h"
#include "../maze/Maze.h"
#include "../maze/MazeNode.h"
#include "../utils/CollisionHandler.h"
#include "../utils/Stopwatch.h"
#include "../utils/Vector.h"
#include <cmath>

using Config::Window::HEIGHT;
using Config::Window::WIDTH;

Player::Player(float width, float height, float scale)
    : Entity(width, height, scale) {}

Player::Player(NodePtr node, float width, float height, float scale)
    : Entity(width, height, scale), current_node_(node) {
  auto maze = Maze::getInstance();
  target_node_ = maze->findNeighbor(current_node_->row_, current_node_->column_,
                                    direction_);
  setPosition(
      maze->getWorldPosition(current_node_->row_, current_node_->column_));
}

void Player::update() {
  //  std::printf("wpos: %f %f", position_.x, position_.y);
  if (moving_)
    move();
  if (overshotTarget()) {
//    updateTargetNode();
    Position pos = Maze::getInstance()->getWorldPosition(target_node_->row_,
                                                         target_node_->column_);
    setPosition(pos);
    moving_ = false;
  }
  notifyObservers();
}

void Player::onCollision(Entity *other) {}

void Player::move() {
  float aspect = static_cast<float>(WIDTH) / HEIGHT;
  float speed = speed_ * Stopwatch::getInstance()->getDeltaTime() * aspect;

  if (direction_ == Direction::LEFT) {
    position_.x -= speed;
  }
  if (direction_ == Direction::RIGHT) {
    position_.x += speed;
  }
  if (direction_ == Direction::UP) {
    position_.y += speed;
  }
  if (direction_ == Direction::DOWN) {
    position_.y -= speed;
  }
}

bool Player::overshotTarget() const {

  if (!target_node_)
    return false;
  Position prev_pos = Maze::getInstance()->getWorldPosition(
      current_node_->row_, current_node_->column_);
  Position target_pos = Maze::getInstance()->getWorldPosition(
      target_node_->row_, target_node_->column_);

  Vector vec1{prev_pos, target_pos};
  Vector vec2{prev_pos, position_};

  float node_2_target = std::pow(vec1.getMagnitude(), 2);
  float node_2_self = std::pow(vec2.getMagnitude(), 2);

  return node_2_self > node_2_target;
}
void Player::updateTargetNode() {
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

EntityType Player::getType() const { return EntityType::Player; }

bool Player::allowsSpawn(Entity *other) {
  return CollisionHandler::checkCollision(this, other);
}
