//
// Created by joachimverleysen on 11/26/24.
//

#include "Player.h"
#include "../maze/Maze.h"
#include "../maze/MazeNode.h"
#include "../utils/CollisionHandler.h"
#include "../utils/Stopwatch.h"

Player::Player(float width, float height, float scale)
    : Entity(width, height, scale) {}

Player::Player(NodePtr node, float width, float height, float scale)
    : Entity(width, height, scale), node_(node) {}

void Player::update() {
  // std::cout << position_.x << " " << position_.y << '\n';
  notifyObservers();
}

void Player::onCollision(Entity *other) {}

void Player::move(Utils::Direction direction) {
  /* if (direction == Utils::Direction::LEFT) {
    position_.x -= speed_;
  }
  if (direction == Utils::Direction::RIGHT) {
    position_.x += speed_;
  }
  if (direction == Utils::Direction::UP) {
    position_.y += speed_;
  }
  if (direction == Utils::Direction::DOWN) {
    position_.y -= speed_;
  } */

  auto maze = Maze::getInstance();
  NodePtr target_node;
  if (direction == Utils::Direction::LEFT) {
    target_node = maze->findNeighbor(node_->row_, node_->column_, 0, -1);
  }
  if (direction == Utils::Direction::RIGHT) {
    target_node = maze->findNeighbor(node_->row_, node_->column_, 0, 1);
  }
  if (direction == Utils::Direction::UP) {
    target_node = maze->findNeighbor(node_->row_, node_->column_, -1, 0);
  }
  if (direction == Utils::Direction::DOWN) {
    target_node = maze->findNeighbor(node_->row_, node_->column_, 1, 0);
  }
  if (target_node) {
    node_ = target_node;
    Position pos =
        maze->getWorldPosition(target_node->row_, target_node->column_);
    setPosition(pos);
  }

  update();
}

EntityType Player::getType() const { return EntityType::Player; }

bool Player::allowsSpawn(Entity *other) {
  return CollisionHandler::checkCollision(this, other);
}
