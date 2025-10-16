#include "Camera.h"
#include "../../logic/maze/Maze.h"

using namespace Config;
Position Camera::world2Window(const Position &position) {
  float x, y;
  // todo: no constant 3 here!
  float w = Window::UNIT_LENGTH * Maze::getInstance()->getXunits();
  float h = Window::UNIT_LENGTH * Maze::getInstance()->getYunits();
  float cx = w / 2, cy = h / 2;
  y = (1 - (position.y + 1) / 2) * h;
  x = cx + position.x;
  y = cy - position.y;

  x = (position.x + 1) / 2 * w;
  y = (1 - (position.y + 1) / 2) * h;
  return Position{x, y};
}

Position Camera::window2World(const Position &position) {
  float w = Window::UNIT_LENGTH * Maze::getInstance()->getXunits();
  float h = Window::UNIT_LENGTH * Maze::getInstance()->getYunits();

  float x = (position.x / w) * 2 - 1;
  float y = 1 - (position.y / h) * 2;
  return Position{x, y};
}
