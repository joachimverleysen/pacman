#include "GameController.h"
#include <SFML/Window/Event.hpp>
#include <optional>
using namespace std;
typedef GameController::Action Action;

std::optional<Direction> getDirection(Action action) {
  switch (action) {
  case GameController::Action::MOVE_LEFT:
    return Direction::LEFT;
  case GameController::Action::MOVE_RIGHT:
    return Direction::RIGHT;
  case GameController::Action::MOVE_UP:
    return Direction::UP;
  case GameController::Action::MOVE_DOWN:
    return Direction::DOWN;
  case GameController::Action::NONE:
    return std::nullopt;
  }
}

void GameController::handleInput(const sf::Event &event) {
  // todo: disable friend class, use setters and getters instead.
  auto action = getAction(event);
  auto player = game_world_.getPlayer();
  std::optional<Direction> direction = getDirection(action);
  if (action == Action::NONE or !direction)
    return;
  if (direction == Utils::getReverseDirection(player->direction_))
    player->reverseDirection();
  if (player->moving_)
    return;
  player->setDirection(direction.value());
  player->startMove();
  auto target = player->target_node_;
  if (target)
    // std::printf("target: row %d, col %d\n", target->row_, target->column_);
    player->setDirection(direction.value());
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

Action GameController::getAction() {
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
