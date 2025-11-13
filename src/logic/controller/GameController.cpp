#include "GameController.h"
#include <SFML/Window/Event.hpp>
#include <optional>
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

void GameController::handleInput(const sf::Event &event) {
  // todo: disable player friend class, use setters and getters instead.
  auto action = getAction(event);
  game_state_.handleAction(action);
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

  return Action::NONE;
}
