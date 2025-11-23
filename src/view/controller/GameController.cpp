#include "GameController.h"
#include "../state/StateManager.h"
#include <SFML/Window/Event.hpp>
#include <optional>
#include <utility>

using namespace std;

GameController::GameController(std::shared_ptr<StateManager> state_manager)
    : state_manager_(std::move(state_manager)),
      game_state_(state_manager_->getCurrentState()) {}
void GameController::handleInput(const sf::Event &event) {
  state_manager_->getAction(event.key.code)();
  if (getAction())
    state_manager_->getCurrentState()->handleAction(getAction().value());
}

std::optional<GameAction> GameController::getAction() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    return GameAction::MOVE_LEFT;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    return GameAction::MOVE_RIGHT;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    return GameAction::MOVE_UP;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    return GameAction::MOVE_DOWN;
  }
  return std::nullopt;
}
