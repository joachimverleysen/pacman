#include "Player.h"
#include "../utils/CollisionHandler.h"
#include "../utils/Vector.h"
#include <cmath>
#include <utility>

Player::Player(NodePtr node, float width, float height)
    : Character(std::move(node), width, height) {}

void Player::onCollision(Entity *other) {
  std::printf("boom\n");
}

EntityType Player::getType() const { return EntityType::Player; }

bool Player::allowsSpawn(Entity *other) {
  return CollisionHandler::checkCollision(this, other);
}
