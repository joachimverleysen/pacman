#ifndef PACMAN_COIN_H
#define PACMAN_COIN_H

#include "Entity.h"
#include "../maze/Wall.h"
#include "../maze/MazeNode.h"

typedef std::shared_ptr<MazeNode> NodePtr;
class Coin : public Entity {
  unsigned int row_;
  unsigned int column_;
public:
  explicit Coin(const NodePtr&);
  Coin(MazePosition);
  MyVector getPosition() const override;
  void update() override {}
  void onCollision(Entity *other) override;
  EntityType getType() const override {return EntityType::Coin;}
  CollisionBehavior getCollisionBehavior(EntityType type) const override {
    return CollisionBehavior::CONSUMABLE;
  };

};


#endif //PACMAN_COIN_H
