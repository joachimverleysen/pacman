#ifndef PLAYER_H
#define PLAYER_H

#include "../utils/Utils.h"
#include "Character.h"
#include <future>

class GameController;
struct MazeNode;

typedef std::shared_ptr<MazeNode> NodePtr;

class Player : public Character {
public:
  Player() = delete;

  Player(NodePtr node, float width, float height);

  /// On collision
  void onCollision(Entity *other) override;

  [[nodiscard]] EntityType getType() const override;

  /// Returns behavior on collision
  CollisionBehavior getCollisionBehavior(EntityType type) const override;
};

#endif // PLAYER_H
