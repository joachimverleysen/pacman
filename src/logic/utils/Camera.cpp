#include "Camera.h"
#include "../../logic/maze/Maze.h"

using namespace Config;
MyVector Camera::world2Window(const MyVector &position) {
  float x, y;
  float w = Window::CELL_WIDTH * Maze::getInstance()->getXunits();
  float h = Window::CELL_WIDTH * Maze::getInstance()->getYunits();
  float cx = w / 2, cy = h / 2;
  y = (1 - (position.y + 1) / 2) * h;
  x = cx + position.x;
  y = cy - position.y;

  x = (position.x + 1) / 2 * w;
  y = (1 - (position.y + 1) / 2) * h;
  return MyVector{x, y};
}

MyVector Camera::window2World(const MyVector &position) {
  float w = Window::CELL_WIDTH * Maze::getInstance()->getXunits();
  float h = Window::CELL_WIDTH * Maze::getInstance()->getYunits();

  float x = (position.x / w) * 2 - 1;
  float y = 1 - (position.y / h) * 2;
  return MyVector{x, y};
}
