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
  Position getPosition() const;
  EntityType getType() const override;
  void onCollision(Entity *other) override {};
  bool allowsSpawn(Entity *other) override { return false; };
  void update() override;
};
#endif // !WALL_H
