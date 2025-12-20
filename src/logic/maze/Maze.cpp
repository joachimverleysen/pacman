#include "Maze.h"
#include "../utils/Utils.h"
#include "MazeNode.h"
#include "Wall.h"
#include <array>
#include <memory>
#include <set>
#include <stdexcept>

Maze *Maze::instance_ = nullptr;

/// Load the grid to initialize the Maze.
/// The grid is the literal representation of the input file, that is, a map of chars
void Maze::loadGrid(Grid &grid) {
  // Numbers are for portals
  // A pair of identical numbers represents a portal pair

  // W (wall)
  // . (path)
  // + (regular node)
  // S (player start node)
  // G (ghost start node)
  // c (coin)
  // C (coin AND node)
  // f (fruit)
  // F (fruit AND node)
  // 1 (portal node)
  // h ('ghost home' node)
  std::set<char> chars = {'+', 'S', '.', 'W', 'G', 'c',
                          'C', '1', 'h', 'f', 'F'};
  grid_ = grid;
  // Initialize node map
  node_map_ = std::vector<std::vector<NodePtr>>(
      grid.size(), std::vector<NodePtr>(grid[0].size(), nullptr));
  // Add nodes to node map

  std::set<char> node_chars = {'+', 'S', 'G', 'C', 'F', '1', 'h'};
  for (int i = 0; i < grid.size(); i++) {
    const auto &vec = grid_[i];
    for (int j = 0; j < vec.size(); j++) {
      char c = vec[j];
      if (chars.find(c) == chars.end())
        throw std::invalid_argument("unexpected char in grid");
      NodePtr node;
      if (node_chars.find(c) != node_chars.end()) {
        node = addNode(i, j);
      }
      if (c == 'S')
        start_node_ = node;
      if (c == 'G')
        ghost_nodes_.push_back(node);
      if (c == 'h')
        ghost_home_nodes_.push_back(node);
      if (c == 'C' || c == 'c')
        coin_positions_.push_back({i, j});
      if (c == 'W') {
        wall_positions_.push_back({i, j});
      }
      if (c == '1')
        addPortal(i, j, 1);
      if (c == 'f' || c == 'F')
        fruit_positions_.push_back({i, j});
    }
  }

  // Find neighbors
  for (int i = 0; i < grid.size(); i++) {
    std::vector<char> vec = grid_[i];
    for (int j = 0; j < vec.size(); j++) {
      if (node_map_[i][j] != nullptr)
        node_map_[i][j]->neighbours_ =
            findAllNeighbors(i, j, EntityType::Ghost);
    }
  }
}

NodePtr Maze::addNode(unsigned int row, unsigned int column) {
  NodePtr node = std::make_shared<MazeNode>(row, column);
  node_map_[row][column] = node;
  return node;
}

std::optional<MazePosition> Maze::findPortal(unsigned int row,
                                             unsigned int col) const {
  for (auto p : portal_pairs_) {
    if (p.first.pos.first == row && p.first.pos.second == col &&
        p.first.index == p.second.index) {
      return p.second.pos;
    }

    if (p.second.pos.first == row && p.second.pos.second == col &&
        p.second.index == p.first.index) {
      return p.first.pos;
    }
  }
  return std::nullopt;
}
NodePtr Maze::findNeighbor(unsigned int row, unsigned int column,
                           Direction direction, EntityType etype) const {
  std::set<char> node_chars = {'+', 'S', 'G', 'C', '1', 'h', 'F'};
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
    if (c == 'W') // Wall
      return nullptr;
    if (c == 'G' && etype != EntityType::Ghost)
      return nullptr;
    else if (c == '.' || c == 'c' || c == 'f' || c == 'S') { // Path
      i += d_row;
      j += d_column;
    } else if (node_chars.find(c) != node_chars.end()) {
      auto node = getNode(i, j);

      // Make sure the Ghosts don't go back to their homes
      if (std::find(ghost_nodes_.begin(), ghost_nodes_.end(), node) != ghost_nodes_.end() &&
      direction == Direction::DOWN)
        return nullptr;

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
  return row < getYunits() and column < getXunits();
}

Neighbours Maze::findAllNeighbors(unsigned int row, unsigned int column,
                                  EntityType etype = EntityType::Ghost) {
  auto node = node_map_[row][column];
  if (!node)
    throw std::invalid_argument("Invalid node position provided");
  Neighbours neighbors;
  neighbors.up = findNeighbor(row, column, Direction::UP, etype);
  neighbors.down = findNeighbor(row, column, Direction::DOWN, etype);
  neighbors.left = findNeighbor(row, column, Direction::LEFT, etype);
  neighbors.right = findNeighbor(row, column, Direction::RIGHT, etype);
  if (findPortal(row, column)) {
    auto pos = findPortal(row, column).value();
    neighbors.portal = getNode(pos.first, pos.second);
  } else
    neighbors.portal = nullptr;
  return neighbors;
}

std::vector<Direction> Maze::getPossibleDirections(NodePtr node,
                                                   EntityType etype) const {
  std::vector<Direction> result = {};
  std::array<Direction, 4> directions = {Direction::UP, Direction::DOWN,
                                         Direction::LEFT, Direction::RIGHT};

  for (auto &d : directions) {
    if (findNeighbor(node->row_, node->column_, d, etype))
      result.push_back(d);
  }
  return result;
}

/// Returns the char at the given position in the input file of the maze
char Maze::at(unsigned int row, unsigned int column) const {
  if (inGridRange(row, column))
    return grid_[row][column];
  return '0';
}

/// Returns the node pointer at the given position or nullptr
NodePtr Maze::getNode(unsigned int row, unsigned int column) const {
  return node_map_[row][column];
}

/// Converts a discrete maze position to a continuous world position
MyVector Maze::getWorldPosition(unsigned int row, unsigned int column) const {
  // World is bounded between -1 and +1, so width = 2.0
  float cell_width = 2.0 / getXunits();
  float cell_height = 2.0 / getYunits();
  float x_center = -1 + (cell_width / 2) + cell_width * column;
  float y_center = 1 - (cell_height / 2) - cell_height * row;
  return MyVector{x_center, y_center};
}

/// Returns the height off a grid cell/maze cell
float Maze::getCellHeight() const { return 2.0 / getYunits(); }

/// Returns the width off a grid cell/maze cell
float Maze::getCellWidth() const { return 2.0 / getXunits(); }

/// Places a portal at the given position (only works if it has a friend portal)
void Maze::addPortal(unsigned int row, unsigned int col, int index) {
  for (auto &p : portal_pairs_) {
    if (p.first.index == index && p.second.index == index)
      throw std::logic_error("Pair already complete");
    if (p.first.index == index && p.second.index == -1) {
      p.second = Portal{{row, col}, index};
      return;
    }
  }
  Portal new_portal{{row, col}, index};
  std::pair<Portal, Portal> new_pair{new_portal, {{-1, -1}, -1}};
  portal_pairs_.push_back(new_pair);
}
