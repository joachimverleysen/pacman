#ifndef PACMAN_FRUIT_H
#define PACMAN_FRUIT_H

#include "Entity.h"
#include "../maze/Wall.h"
#include "../maze/MazeNode.h"

typedef std::shared_ptr<MazeNode> NodePtr;
class Fruit : public Entity {
  unsigned int row_;
  unsigned int column_;
public:
  explicit Fruit(const NodePtr&);
  Fruit(MazePosition);
  MyVector getPosition() const override;
  void update() override {}
  void onCollision(Entity *other) override;
  EntityType getType() const override {return EntityType::Fruit;}
  CollisionBehavior getCollisionBehavior(EntityType type) const override {
    return CollisionBehavior::CONSUMABLE;
  };
};


#endif //PACMAN_FRUIT_H