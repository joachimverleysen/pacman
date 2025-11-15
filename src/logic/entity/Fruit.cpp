#include "Fruit.h"
#include "../maze/Maze.h"

MyVector Fruit::getPosition() const {
  return Maze::getInstance()->getWorldPosition(row_, column_);
}

Fruit::Fruit(const NodePtr& node)
: row_(node->row_), column_(node->column_) {
}

Fruit::Fruit(std::pair<int, int> pos)
: row_(pos.first), column_(pos.second) {
  setPosition(Maze::getInstance()->getWorldPosition(row_, column_));
}

void Fruit::onCollision(Entity *other) {
  if (other->getType() == EntityType::Player)
    deactivate();
}
