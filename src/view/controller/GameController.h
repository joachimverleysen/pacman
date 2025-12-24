#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../../logic/World.h"
#include "SFML/Window/Event.hpp"

class GameController {

  std::shared_ptr<StateManager> state_manager_;
  std::shared_ptr<State> game_state_;

public:

public:

  friend World;
  explicit GameController(std::shared_ptr<StateManager> state_manager);

  /// handles an event
  void handleInput(const sf::Event &event);

  /// fetches an action
  [[maybe_unused]] static std::optional<GameAction> getAction();

};

#endif // GAMECONTROLLER_H
