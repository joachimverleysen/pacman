#ifndef MAZE_NODE_H
#define MAZE_NODE_H
#include "../utils/MyVector.h"
#include <memory>
#include <vector>

struct MazeNode;
typedef std::shared_ptr<MazeNode> NodePtr;
struct Neighbours {
  NodePtr up;
  NodePtr down;
  NodePtr left;
  NodePtr right;
  NodePtr portal;
};

struct MazeNode {
  enum class Type { Start = 0, Ghost = 1 };
  int row_;
  int column_;
  Type type_;
  Neighbours neighbours_;

  MyVector getPosition() const;

  Type getType() const;

  void setType(Type);

  MazeNode(int row, int column) : row_(row), column_(column) {}
};
#endif // !MAZE_NODE_H
