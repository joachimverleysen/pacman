#ifndef PACMAN_UTILS_H
#define PACMAN_UTILS_H

// Type defs
#include <optional>
#include <string>
#include "MyVector.h"

class Entity;
enum class Direction { LEFT, RIGHT, UP, DOWN, NONE };

enum class CollisionBehavior { KILLING, CONSUMABLE, NONE };

enum class GameAction {
  MOVE_LEFT,
  MOVE_RIGHT,
  MOVE_UP,
  MOVE_DOWN,
  NONE, VICTORY
};

namespace MyFont {
inline std::string LIBER = "assets/font/liber.ttf";
inline std::string PACFONT= "assets/font/Pacfont.ttf";
}
namespace Utils {
// State
namespace StateNS {
enum class Type {WORLD, PAUSE, GAME_OVER, VICTORY, STARTMENU};
enum class Action {};
}

inline MyVector positionAfterMove(MyVector pos, Direction direction, float offset) {
  switch (direction) {
    case Direction::LEFT:
      pos.x -= offset;
      break;
    case Direction::RIGHT:
      pos.x += offset;
      break;
    case Direction::UP:
      pos.y += offset;
      break;
    case Direction::DOWN:
      pos.y -= offset;
      break;
    case Direction::NONE:
      break;
  }
  return pos;
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
inline std::optional<Direction> getDirection(GameAction action) {
  switch (action) {
  case GameAction::MOVE_LEFT:
    return Direction::LEFT;
  case GameAction::MOVE_RIGHT:
    return Direction::RIGHT;
  case GameAction::MOVE_UP:
    return Direction::UP;
  case GameAction::MOVE_DOWN:
    return Direction::DOWN;
  case GameAction::NONE:
    return std::nullopt;
  }
  return std::nullopt;
}
} // namespace Utils
#endif // PACMAN_UTILS_H
