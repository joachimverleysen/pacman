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

  void onCollision(Entity *other) override;

  void onDeath();

  [[nodiscard]] EntityType getType() const override;

  void move(float offset);

  CollisionBehavior getCollisionBehavior(EntityType type) const override;

};

#endif // PLAYER_H
