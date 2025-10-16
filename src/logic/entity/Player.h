//
// Created by joachimverleysen on 11/26/24.
//

#ifndef DOODLEJUMP_PLAYER_H
#define DOODLEJUMP_PLAYER_H

#include "../../configure/constants.h"
#include "../utils/Utils.h"
#include "Entity.h"
#include "iostream"
#include <future>

class GameController;
class MazeNode;
typedef std::shared_ptr<MazeNode> NodePtr;

class Player : public Entity {
  float speed_{Config::Player::SPEED * 0.01f};
  Direction direction_{Direction::LEFT};
  bool moving_{false};

public:
  NodePtr current_node_;
  NodePtr target_node_;

public:
  friend GameController;
  Player() = default;

  Player(float width, float height, float scale);

  Player(NodePtr node, float width, float height, float scale);

  void move();

  void update() override;

  void updateTargetNode();

  bool overshotTarget() const;

  bool allowsSpawn(Entity *other) override;

  void onCollision(Entity *other) override;

  EntityType getType() const override;
};

#endif // DOODLEJUMP_PLAYER_H
