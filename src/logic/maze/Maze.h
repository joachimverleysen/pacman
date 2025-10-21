#ifndef MAZE_H
#define MAZE_H

#include "../utils/Utils.h"
#include "MazeNode.h"

typedef std::vector<std::vector<char>> Grid;

class Maze {
private:
  static Maze *instance_;
  Maze() {};

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
  Grid grid_;
  std::vector<std::vector<NodePtr>> node_map_;
  NodePtr start_node_;

public:
  void loadGrid(Grid &grid);
  unsigned int getXunits() const { return grid_[0].size(); }
  unsigned int getYunits() const { return grid_.size(); }
  float getCellWidth() const;
  float getCellHeight() const;
  NodePtr addNode(unsigned int row, unsigned int column);
  Neighbours findAllNeighbors(unsigned int row, unsigned int column);
  NodePtr findNeighbor(unsigned int row, unsigned int column,
                       Direction direction) const;

  char at(unsigned int row, unsigned int column) const;
  NodePtr getNode(unsigned int row, unsigned int column) const;

  Position
  getWorldPosition(unsigned int row,
                   unsigned int column) const; // Returns center of the 'square'
  bool inGridRange(unsigned int row, unsigned int column) const;
};
#endif // !MAZE_H
