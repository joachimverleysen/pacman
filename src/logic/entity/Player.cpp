//
// Created by joachimverleysen on 11/26/24.
//

#include "Player.h"
#include "../utils/CollisionHandler.h"
#include "../utils/Stopwatch.h"

void Player::update() {
  // todo
  if (position_.x > 0.5) {
    deactivate();
  }
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

  float delta_time = Stopwatch::getInstance()->getDeltaTime();
  update();
}

EntityType Player::getType() const { return EntityType::Player; }

bool Player::allowsSpawn(Entity *other) {
  return CollisionHandler::checkCollision(this, other);
}
Player::Player(float width, float height, float scale)
    : Entity(width, height, scale) {}
