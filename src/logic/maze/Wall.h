#ifndef WALL_H
#define WALL_H
#include "../entity/Entity.h"

typedef std::pair<int, int> MazePosition;
class Maze;
class Wall : public Entity {
  /* unsigned int row_;
  unsigned int column_; */
  std::vector<MazePosition> positions_;

public:
  friend Maze;

public:
  // Wall(unsigned int row, unsigned int column);
  Wall(std::vector<MazePosition> &positions);

  std::vector<MazePosition> getPositions() const;
  MyVector getPosition() const override;
  EntityType getType() const override;
  void onCollision(Entity *other) override {};
  void update() override;
  CollisionBehavior getCollisionBehavior(EntityType type) const override {
    return  CollisionBehavior::NONE;
  };
};
#endif // !WALL_H
