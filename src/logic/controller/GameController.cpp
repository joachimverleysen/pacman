//
// Created by joachimverleysen on 11/26/24.
//

#include "GameController.h"
#include <SFML/Window/Event.hpp>
#include <iostream>
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
  auto action = getAction(event);
  auto player = game_world_.getPlayer();
  std::optional<Direction> direction = getDirection(action);
  if (action == Action::NONE)
    return;
  if (!direction)
    return;
  if (player->moving_)
    return;
  player->direction_ = direction.value();
  player->moving_ = true;
  auto target = player->target_node_;
  if (target)
    std::printf("target: row %d, col %d\n", target->row_, target->column_);
  if (action == Action::MOVE_LEFT) {
    player->setState(Entity::State::LEFT);
  }
  if (action == Action::MOVE_RIGHT) {
    player->setState(Entity::State::RIGHT);
  }
  if (action == Action::MOVE_UP) {
    player->setState(Entity::State::UP);
  }
  if (action == Action::MOVE_DOWN) {
    player->setState(Entity::State::DOWN);
  }
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
