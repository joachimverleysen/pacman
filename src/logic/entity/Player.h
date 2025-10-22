#ifndef PLAYER_H
#define PLAYER_H

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
  Player() = delete;

  Player(NodePtr node, float width, float height);

  bool allowsSpawn(Entity *other) override;

  void onCollision(Entity *other) override;

  [[nodiscard]] EntityType getType() const override;
};

#endif // PLAYER_H
