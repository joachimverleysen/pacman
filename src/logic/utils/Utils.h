#ifndef PACMAN_UTILS_H
#define PACMAN_UTILS_H

// Type defs
#include <string>
class Entity;
enum class Direction { LEFT, RIGHT, UP, DOWN, NONE };

namespace Utils {

// Direction
inline Direction getReverseDirection(Direction direction) {
  switch (direction) {
  case Direction::NONE:
    return Direction::NONE;
  case Direction::LEFT:
    return Direction::RIGHT;
  case Direction::RIGHT:
    return Direction::LEFT;
  case Direction::UP:
    return Direction::DOWN;
  case Direction::DOWN:
    return Direction::UP;
  }
} // namespace Utils
inline Direction getDirection(int num) {
  switch (num) {
  case 0:
    return Direction::LEFT;
  case 1:
    return Direction::RIGHT;
  case 2:
    return Direction::UP;
  case 3:
    return Direction::DOWN;
  case 4:
    return Direction::NONE;
  }
}
} // namespace Utils
#endif // PACMAN_UTILS_H
