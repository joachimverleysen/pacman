#ifndef PACMAN_UTILS_H
#define PACMAN_UTILS_H

// Type defs
#include <string>
class Entity;
enum class Direction { NONE, LEFT, RIGHT, UP, DOWN };

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
}
#endif // PACMAN_UTILS_H
