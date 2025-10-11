#ifndef MAZE_NODE_H
#define MAZE_NODE_H
#include "../utils/Position.h"
#include <memory>
#include <vector>

struct MazeNode;
typedef std::shared_ptr<MazeNode> NodePtr;
struct Neighbours {
  NodePtr up;
  NodePtr down;
  NodePtr left;
  NodePtr right;
};

struct MazeNode {
  int row_;
  int column_;
  Neighbours neighbours_;

  MazeNode(int row, int column) : row_(row), column_(column) {}
};
#endif // !MAZE_NODE_H
