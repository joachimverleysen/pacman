#ifndef WALL_H
#include "Entity.h"

class Wall : public Entity {
  unsigned int row_;
  unsigned int column_;

public:
  Wall(unsigned int row, unsigned int column);

  Position getPosition() const;
  EntityType getType() const override;
  void onCollision(Entity *other) override {};
  bool allowsSpawn(Entity *other) override { return false; };
  void update() override;
};
#endif // !WALL_H
