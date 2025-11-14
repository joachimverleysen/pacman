#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../../logic/World.h"
#include "../../../cmake-build-debug/_deps/sfml-src/include/SFML/Window/Event.hpp"

class GameController {

  std::shared_ptr<StateManager> state_manager_;
  std::shared_ptr<State> game_state_;

public:

public:

  friend World;
  explicit GameController(std::shared_ptr<StateManager> state_manager);

  void handleInput(const sf::Event &event);

  [[maybe_unused]] static Action getAction();

  static Action getAction(const sf::Event &event);

  static std::optional<Direction> getDirection(Action action);

  void pauseAction();
};

#endif // GAMECONTROLLER_H
