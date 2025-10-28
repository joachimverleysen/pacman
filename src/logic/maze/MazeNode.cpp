#include "MazeNode.h"
#include "Maze.h"

Position MazeNode::getPosition() const {
  return Maze::getInstance()->getWorldPosition(row_, column_);
}

MazeNode::Type MazeNode::getType() const { return type_; }

void MazeNode::setType(Type type) { type_ = type; }
