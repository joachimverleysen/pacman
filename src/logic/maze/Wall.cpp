#include "Wall.h"
#include "../maze/Maze.h"

// Wall::Wall(unsigned int row, unsigned int column) : row_(row),
// column_(column) {}

Wall::Wall(std::vector<MazePosition> &positions) : positions_(positions) {}

Position Wall::getPosition() const {
  // Compute top left corner
  auto maze = Maze::getInstance();
  float x, y;

  /* x = -1 + maze->getCellWidth() * column_;
  y = 1 - maze->getCellHeight() * row_; */
  // return Position{x, y};
  return {0, 0};
}

void Wall::update() {
    notifyObservers();
}
EntityType Wall::getType() const { return EntityType::Wall; }

std::vector<MazePosition> Wall::getPositions() const {
  return positions_;
}
