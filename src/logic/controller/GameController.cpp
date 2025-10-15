//
// Created by joachimverleysen on 11/26/24.
//

#include "GameController.h"
#include <SFML/Window/Event.hpp>
#include <iostream>
using namespace std;

void GameController::handleInput() {
  auto action = getAction();
  if (action == GameController::Action::MOVE_LEFT) {
    game_world_.getPlayer()->move(Utils::Direction::LEFT);
    game_world_.getPlayer()->setState(Entity::State::LEFT);
  }
  if (action == GameController::Action::MOVE_RIGHT) {
    game_world_.getPlayer()->move(Utils::Direction::RIGHT);
    game_world_.getPlayer()->setState(Entity::State::RIGHT);
  }
  if (action == GameController::Action::MOVE_UP) {
    game_world_.getPlayer()->move(Utils::Direction::UP);
    game_world_.getPlayer()->setState(Entity::State::UP);
  }
  if (action == GameController::Action::MOVE_DOWN) {
    game_world_.getPlayer()->move(Utils::Direction::DOWN);
    game_world_.getPlayer()->setState(Entity::State::DOWN);
  }
}

void GameController::handleInput(const sf::Event &event) {
  auto action = getAction(event);
  if (action == GameController::Action::MOVE_LEFT) {
    game_world_.getPlayer()->setState(Entity::State::LEFT);
    game_world_.getPlayer()->move(Utils::Direction::LEFT);
  }
  if (action == GameController::Action::MOVE_RIGHT) {
    game_world_.getPlayer()->setState(Entity::State::RIGHT);
    game_world_.getPlayer()->move(Utils::Direction::RIGHT);
  }
  if (action == GameController::Action::MOVE_UP) {
    game_world_.getPlayer()->setState(Entity::State::UP);
    game_world_.getPlayer()->move(Utils::Direction::UP);
  }
  if (action == GameController::Action::MOVE_DOWN) {
    game_world_.getPlayer()->setState(Entity::State::DOWN);
    game_world_.getPlayer()->move(Utils::Direction::DOWN);
  }
}

GameController::Action GameController::getAction(const sf::Event &event) {
  GameController::Action action;
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

GameController::Action GameController::getAction() {
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
