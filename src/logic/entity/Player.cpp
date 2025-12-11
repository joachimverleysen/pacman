#include "Player.h"
#include "../utils/CollisionHandler.h"
#include "../utils/Vector.h"
#include <cmath>
#include <utility>

Player::Player(NodePtr node, float width, float height)
    : Character(std::move(node), width, height) {}

void Player::onCollision(Entity *other) {}

EntityType Player::getType() const { return EntityType::Player; }

CollisionBehavior Player::getCollisionBehavior(EntityType type) const {
    return CollisionBehavior::KILLING;
}
