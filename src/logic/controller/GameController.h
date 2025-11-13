#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../World.h"
#include <SFML/Window/Event.hpp>

class GameController {

  State &game_state_;

public:

public:

  friend World;
  explicit GameController(State &game_world) : game_state_(game_world) {};

  void handleInput(const sf::Event &event);

  [[maybe_unused]] static Action getAction();

  static Action getAction(const sf::Event &event);

  static std::optional<Direction> getDirection(Action action);
};

#endif // GAMECONTROLLER_H
