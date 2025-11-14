#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../World.h"
#include <SFML/Window/Event.hpp>

class GameController {

  std::shared_ptr<StateManager> state_manager_;
  std::shared_ptr<State> game_state_;

public:

public:

  friend World;
  explicit GameController(std::shared_ptr<StateManager> state_manager);

  void handleInput(const sf::Event &event);

  [[maybe_unused]] static std::optional<GameAction> getAction();

  static GameAction getAction(const sf::Event &event);

};

#endif // GAMECONTROLLER_H
