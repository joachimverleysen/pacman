#include "Maze.h"
#include "MazeNode.h"
#include <memory>
#include <set>
#include <stdexcept>

Maze *Maze::instance_ = nullptr;

void Maze::loadGrid(Grid &grid) {
  std::set<char> chars = {'+', 'S', '.', 'W'};
  grid_ = grid;
  // Initialize node map
  node_map_ = std::vector<std::vector<NodePtr>>(
      grid.size(), std::vector<NodePtr>(grid[0].size(), nullptr));
  // Add nodes to node map
  for (int i = 0; i < grid.size(); i++) {
    const auto &vec = grid_[i];
    for (int j = 0; j < vec.size(); j++) {
      char c = vec[j];
      if (chars.find(c) == chars.end())
        throw std::invalid_argument("unexpected char in grid");
      if (c == '+')
        addNode(i, j);
      else if (c == 'S') {
        NodePtr node = addNode(i, j);
        start_node_ = node;
      }
    }
  }

  // Find neighbors
  for (int i = 0; i < grid.size(); i++) {
    std::vector<char> vec = grid_[i];
    for (int j = 0; j < vec.size(); j++) {
      if (node_map_[i][j] != nullptr)
        node_map_[i][j]->neighbours_ = findAllNeighbors(i, j);
    }
  }
}

NodePtr Maze::addNode(unsigned int row, unsigned int column) {
  NodePtr node = std::make_shared<MazeNode>(row, column);
  node_map_[row][column] = node;
  return node;
}

NodePtr Maze::findNeighbor(unsigned int row, unsigned int column,
                           Direction direction) const {
  std::set<char> node_chars = {'+', 'S'};
  if (node_chars.find(at(row, column)) == node_chars.end())
    throw std::invalid_argument("Invalid node position provided");

  int d_row, d_column;
  switch (direction) {
  case Direction::LEFT:
    d_row = 0;
    d_column = -1;
    break;
  case Direction::RIGHT:
    d_row = 0;
    d_column = 1;
    break;
  case Direction::UP:
    d_row = -1;
    d_column = 0;
    break;
  case Direction::DOWN:
    d_row = 1;
    d_column = 0;
    break;
  case Direction::NONE:
    throw std::invalid_argument("Can't find neighbor for Direction::NONE");
  }
  unsigned int i = row + d_row, j = column + d_column;
  if (!inGridRange(i, j))
    return nullptr;
  char c = at(i, j);
  while (c != '0') {
    if (c == 'W')  // Wall
      return nullptr;
    else if (c == '.') {  // Path
      i += d_row;
      j += d_column;
    } else if (node_chars.find(c) != node_chars.end()) {
      auto node = getNode(i, j);
      if (!node)
        throw std::logic_error(
            "A node was expected in the node map but not found.");
      return node;
    }
    c = at(i, j);
  }
  return nullptr;
}

bool Maze::inGridRange(unsigned int row, unsigned int column) const {
  return row < getYunits() and
         column < getXunits();
}

Neighbours Maze::findAllNeighbors(unsigned int row, unsigned int column) {
  auto node = node_map_[row][column];
  if (!node)
    throw std::invalid_argument("Invalid node position provided");
  Neighbours neighbors;
  neighbors.up = findNeighbor(row, column, Direction::UP);
  neighbors.down = findNeighbor(row, column, Direction::DOWN);
  neighbors.left = findNeighbor(row, column, Direction::LEFT);
  neighbors.right = findNeighbor(row, column, Direction::RIGHT);
  return neighbors;
}

char Maze::at(unsigned int row, unsigned int column) const {
  if (inGridRange(row, column))
    return grid_[row][column];
  return '0';
}

NodePtr Maze::getNode(unsigned int row, unsigned int column) const {
  return node_map_[row][column];
}

Position Maze::getWorldPosition(unsigned int row, unsigned int column) const {
  // World is bounded between -1 and +1, so width = 2.0
  float cell_width = 2.0 / getXunits();
  float cell_height = 2.0 / getYunits();
  float x_center = -1 + (cell_width / 2) + cell_width * column;
  float y_center = 1 - (cell_height / 2) - cell_height * row;
  return Position{x_center, y_center};
}

float Maze::getCellHeight() const { return 2.0 / getYunits(); }

float Maze::getCellWidth() const { return 2.0 / getXunits(); }
