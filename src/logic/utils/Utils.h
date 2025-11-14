#ifndef PACMAN_UTILS_H
#define PACMAN_UTILS_H

// Type defs
#include <optional>
#include <string>

class Entity;
enum class Direction { LEFT, RIGHT, UP, DOWN, NONE };

enum class Action { MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, PAUSE, NONE };
namespace Utils {

// State
namespace StateNS {
enum class Type {WORLD, PAUSE};
}

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
  return Direction::LEFT;
}
typedef Action Action;
inline std::optional<Direction> getDirection(Action action) {
  switch (action) {
  case Action::MOVE_LEFT:
    return Direction::LEFT;
  case Action::MOVE_RIGHT:
    return Direction::RIGHT;
  case Action::MOVE_UP:
    return Direction::UP;
  case Action::MOVE_DOWN:
    return Direction::DOWN;
  case Action::NONE:
    return std::nullopt;
  }
  return std::nullopt;
}
} // namespace Utils
#endif // PACMAN_UTILS_H
