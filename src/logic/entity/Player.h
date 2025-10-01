//
// Created by joachimverleysen on 11/26/24.
//

#ifndef DOODLEJUMP_PLAYER_H
#define DOODLEJUMP_PLAYER_H

#include "../../configure/constants.h"
#include "../utils/Utils.h"
#include "Entity.h"
#include "iostream"

class Player : public Entity {
  float speed_{Config::Player::SPEED * Config::Window::BASE_SCALE};

public:
  Player() = default;

  Player(float width, float height, float scale);

  void move(Utils::Direction direction);

  void update() override;

  bool allowsSpawn(Entity *other) override;

  void onCollision(Entity *other) override;

  EntityType getType() const override;
};

#endif // DOODLEJUMP_PLAYER_H
