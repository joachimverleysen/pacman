//
// Created by joachimverleysen on 11/26/24.
//

#include "Player.h"
#include "../CollisionHandler.h"

void Player::update(float delta_time) {

  if (position_.x > 200)
    deactivate();
  notifyObservers();
}

void Player::onCollision(Entity *other) {}

void Player::move(Utils::Direction direction) {
  if (direction == Utils::Direction::LEFT) {
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
  }
  notifyObservers();
}

EntityType Player::getType() const { return EntityType::Player; }

bool Player::allowsSpawn(Entity *other) {
  return CollisionHandler::checkCollision(this, other);
}
Player::Player(float width, float height, float scale)
    : Entity(width, height, scale) {}
