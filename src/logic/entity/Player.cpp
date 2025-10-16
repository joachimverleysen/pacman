//
// Created by joachimverleysen on 11/26/24.
//

#include "Player.h"
#include "../utils/CollisionHandler.h"
#include "../utils/Vector.h"
#include <cmath>

Player::Player(NodePtr node, float width, float height, float scale)
    : Character(node, width, height, scale) {}

void Player::onCollision(Entity *other) {}

EntityType Player::getType() const { return EntityType::Player; }

bool Player::allowsSpawn(Entity *other) {
  return CollisionHandler::checkCollision(this, other);
}
