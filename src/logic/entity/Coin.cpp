#include "Coin.h"
#include "../maze/Maze.h"
#include "../utils/Camera.h"

MyVector Coin::getPosition() const {
  return Maze::getInstance()->getWorldPosition(row_, column_);
}

Coin::Coin(const NodePtr& node)
: row_(node->row_), column_(node->column_) {
}

Coin::Coin(std::pair<int, int> pos)
: row_(pos.first), column_(pos.second) {
  setPosition(Maze::getInstance()->getWorldPosition(row_, column_));
}

void Coin::onCollision(Entity *other) {
  if (other->getType() == EntityType::Player)
    deactivate();

}
