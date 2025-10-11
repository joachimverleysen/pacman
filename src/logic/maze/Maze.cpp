#include "Maze.h"
#include "MazeNode.h"
#include <iostream>
#include <memory>
#include <stdexcept>

Maze *Maze::instance_ = nullptr;
void Maze::loadGrid(Grid &grid) {
  grid_ = grid;
  // Initialize node map
  node_map_ = std::vector<std::vector<NodePtr>>(
      grid.size(), std::vector<NodePtr>(grid[0].size(), nullptr));
  // Add nodes to node map
  for (int i = 0; i < grid.size(); i++) {
    std::vector<char> vec = grid_[i];
    for (int j = 0; j < vec.size(); j++) {
      char c = vec[j];
      if (c == '+')
        try {
          addNode(i, j);
        } catch (std::invalid_argument &e) {
          std::cout << e.what() << '\n';
        } catch (std::logic_error &e) {
          std::cout << e.what() << '\n';
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

void Maze::addNode(int row, int column) {
  // std::cout << "adding at " << row << " " << column << '\n';
  NodePtr node = std::make_shared<MazeNode>(row, column);
  node_map_[row][column] = node;
}

NodePtr Maze::findNeighbor(int row, int column, int d_row, int d_column) {
  if (d_row != 0 and d_column != 0)
    throw std::invalid_argument("Invalid combination of directional vectors");

  if (at(row, column) != '+')
    throw std::invalid_argument("Invalid node position provided");

  int i = row + d_row, j = column + d_column;
  while (at(i, j) != '0') {
    if (at(i, j) == 'X')
      return nullptr;
    else if (at(i, j) == '.') {
      i += d_row;
      j += d_column;
    } else if (at(i, j) == '+') {
      auto node = getNode(i, j);
      if (!node)
        throw std::logic_error(
            "A node was expected in the node map but not found.");
      return node;
    }
  }
  return nullptr;
}

Neighbours Maze::findAllNeighbors(int row, int column) {
  auto node = node_map_[row][column];
  if (!node)
    throw std::invalid_argument("Invalid node position provided");
  Neighbours neighbors;
  neighbors.up = findNeighbor(row, column, 0, -1);
  neighbors.down = findNeighbor(row, column, 0, 1);
  neighbors.left = findNeighbor(row, column, -1, 0);
  neighbors.right = findNeighbor(row, column, 1, 0);
  return neighbors;
}

char Maze::at(int row, int column) const {
  if (0 <= row and row < getYunits() and 0 <= column and column < getXunits())
    return grid_[row][column];
  return '0';
}

NodePtr Maze::getNode(int row, int column) const {
  return node_map_[row][column];
}

Position Maze::getWorldPosition(int row, int column) const {
  float cell_width = 2.0 / getXunits();
  float cell_height = 2.0 / getYunits();
  float x_center = -1 + (cell_width / 2) + cell_width * column;
  float y_center = 1 - (cell_height / 2) - cell_height * row;
  return Position{x_center, y_center};
}
