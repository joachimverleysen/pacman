#ifndef MAZE_H
#define MAZE_H

#include "../utils/Utils.h"
#include "MazeNode.h"

typedef std::vector<std::vector<char>> Grid;

class Maze {
private:
  static Maze *instance_;
  Maze() {};

  Grid grid_;

public:
  Maze(const Maze &) = delete;
  Maze &operator=(const Maze &) = delete;

  static Maze *getInstance() {
    if (!instance_) {
      instance_ = new Maze();
    }
    return instance_;
  }

public:
  std::vector<std::vector<NodePtr>> node_map_;

public:
  void loadGrid(Grid &grid);
  unsigned int getXunits() const { return grid_[0].size(); }
  unsigned int getYunits() const { return grid_.size(); }
  void addNode(int row, int column);
  Neighbours findAllNeighbors(int row, int column);
  NodePtr findNeighbor(int row, int column, Direction direction);

  char at(int row, int column) const;
  NodePtr getNode(int row, int column) const;

  Position getWorldPosition(int row,
                            int column) const; // Returns center of the 'square'
};
#endif // !MAZE_H
