#include "GameController.h"
#include "../state/StateManager.h"
#include "../../logic/State.h"
#include "../../logic/PauseMenu.h"
#include <SFML/Window/Event.hpp>
#include <optional>
#include <utility>

using namespace std;


// Helper function
std::optional<Direction> GameController::getDirection(Action action) {
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
}

void GameController::pauseAction() {
  if (state_manager_->getCurrentType() == StateNS::Type::PAUSE) {
    state_manager_->popCurrentState();
    return;
  }
  if (state_manager_->getCurrentType() == StateNS::Type::GAME_OVER)
    return;

  auto factory = state_manager_->getFactory();
  std::shared_ptr<PauseMenu> state_new = std::make_shared<PauseMenu>(factory);
  state_manager_->pushState(state_new);
}
void GameController::handleInput(const sf::Event &event) {
  // todo: disable player friend class, use setters and getters instead.
  auto action = getAction(event);
  if (action == Action::SPACE) {
    pauseAction();
  }
  game_state_->handleAction(action);
}

Action GameController::getAction(const sf::Event &event) {
  Action action;
  switch (event.key.code) {
  case sf::Keyboard::Left:
    action = Action::MOVE_LEFT;
    break;
  case sf::Keyboard::Right:
    action = Action::MOVE_RIGHT;
    break;
  case sf::Keyboard::Up:
    action = Action::MOVE_UP;
    break;
  case sf::Keyboard::Down:
    action = Action::MOVE_DOWN;
    break;
  case sf::Keyboard::Space:
    action = Action::SPACE;
    break;
  default:
    action = Action::NONE;
    break;
  }
  return action;
}

[[maybe_unused]] Action GameController::getAction() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    return Action::MOVE_LEFT;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    return Action::MOVE_RIGHT;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    return Action::MOVE_UP;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    return Action::MOVE_DOWN;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    return Action::SPACE;
  }

  return Action::NONE;
}

GameController::GameController(std::shared_ptr<StateManager> state_manager)
: state_manager_(std::move(state_manager)), game_state_(state_manager_->getCurrentState()) {

}
