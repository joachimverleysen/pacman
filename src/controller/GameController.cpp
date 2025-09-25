//
// Created by joachimverleysen on 11/26/24.
//

#include <iostream>
#include "GameController.h"
using namespace std;

void GameController::handleInput() {
    auto action = getAction();
    if (action == GameController::Action::MOVE_LEFT) {
        game_world_.getPlayer()->move(Utils::Direction::LEFT);
        game_world_.getPlayer()->setState(PacmanState::LEFT);
    }
    if (action == GameController::Action::MOVE_RIGHT) {
        game_world_.getPlayer()->move(Utils::Direction::RIGHT);
        game_world_.getPlayer()->setState(PacmanState::RIGHT);
    }
    if (action == GameController::Action::MOVE_UP) {
        game_world_.getPlayer()->move(Utils::Direction::UP);
        game_world_.getPlayer()->setState(PacmanState::UP);
    }
    if (action == GameController::Action::MOVE_DOWN) {
        game_world_.getPlayer()->move(Utils::Direction::DOWN);
        game_world_.getPlayer()->setState(PacmanState::DOWN);
    }
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

