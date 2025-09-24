//
// Created by joachimverleysen on 11/26/24.
//

#include "Player.h"
#include "../CollisionHandler.h"

void Player::update(float delta_time) { notifyObservers(); }

void Player::onCollision(Entity *other) {}

void Player::move(Utils::Direction direction) {
  if (direction == Utils::Direction::LEFT) {
    position_.x -= speed_;
    state_ = EntityState::LEFT;
  }
  if (direction == Utils::Direction::RIGHT) {
    position_.x += speed_;
    state_ = EntityState::RIGHT;
  }
  notifyObservers();
}

EntityType Player::getType() const { return EntityType::Player; }

bool Player::allowsSpawn(Entity *other) {
  return CollisionHandler::checkCollision(this, other);
}
