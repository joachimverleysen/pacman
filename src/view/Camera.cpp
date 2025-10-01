#include "Camera.h"
#include <algorithm>

Position Camera::world2SFML(const Position &position) {
  float x, y;
  float w = Config::Window::WIDTH;
  float h = Config::Window::HEIGHT;
  float cx = w / 2, cy = h / 2;
  float scale = std::min(h, w)/2;
  // x = (position.x + 1) / 2 * w;
  // y = (1 - (position.y + 1) / 2) * h;
  x = cx + position.x * scale;
  y = cy - position.y * scale;
  return Position{x, y};
}
