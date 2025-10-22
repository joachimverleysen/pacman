#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../World.h"
#include <SFML/Window/Event.hpp>

class GameController {

  World &game_world_;

public:
  enum class Action { MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, NONE };

public:
  explicit GameController(World &game_world) : game_world_(game_world) {};

  void handleInput(const sf::Event &event);

  [[maybe_unused]] static Action getAction();

  static Action getAction(const sf::Event &event);
};

#endif // GAMECONTROLLER_H
