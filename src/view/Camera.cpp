#include "Camera.h"
#include "../logic/maze/Maze.h"
#include <algorithm>

using Config::Arena::X_UNITS;
using Config::Arena::Y_UNITS;
using Config::Window::UNIT_LENGTH;
Position Camera::world2SFML(const Position &position) {
  float x, y;
  // todo: no constant 3 here!
  float w = UNIT_LENGTH * Maze::getInstance()->getXunits();
  float h = UNIT_LENGTH * Maze::getInstance()->getYunits();
  float cx = w / 2, cy = h / 2;
  float scale = std::min(h, w) / 2;
  // x = (position.x + 1) / 2 * w;
  // y = (1 - (position.y + 1) / 2) * h;
  /* x = cx + position.x * scale;
  y = cy - position.y * scale; */

  x = (position.x + 1) / 2 * w;
  y = (1 - (position.y + 1) / 2) * h;
  return Position{x, y};
}
