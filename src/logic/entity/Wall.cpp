#include "Wall.h"
#include "../maze/Maze.h"
#include "Entity.h"
#include "EntityType.h"

Wall::Wall(unsigned int row, unsigned int column) : row_(row), column_(column) {}
Position Wall::getPosition() const {
  // Compute top left corner
  auto maze = Maze::getInstance();
  float x, y;

  x = -1 + maze->getCellWidth() * column_;
  y = 1 - maze->getCellHeight() * row_;
  return Position{x, y};
}

void Wall::update() {
//  notifyObservers();
}
EntityType Wall::getType() const { return EntityType::Wall; }
