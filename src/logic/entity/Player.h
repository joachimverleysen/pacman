#ifndef DOODLEJUMP_PLAYER_H
#define DOODLEJUMP_PLAYER_H

#include "../../configure/constants.h"
#include "../utils/Utils.h"
#include "Character.h"
#include "iostream"
#include <future>

class GameController;
class MazeNode;
typedef std::shared_ptr<MazeNode> NodePtr;

class Player : public Character {

public:
  friend GameController;
  Player() = delete;

  Player(float width, float height, float scale);

  Player(NodePtr node, float width, float height, float scale);

  bool allowsSpawn(Entity *other) override;

  void onCollision(Entity *other) override;

  EntityType getType() const override;
};

#endif // DOODLEJUMP_PLAYER_H
