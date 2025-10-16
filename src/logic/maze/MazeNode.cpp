#include "MazeNode.h"
#include "Maze.h"

Position MazeNode::getPosition() const {
  return Maze::getInstance()->getWorldPosition(row_, column_);
}
