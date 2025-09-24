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
    }
    if (action == GameController::Action::MOVE_RIGHT) {
        game_world_.getPlayer()->move(Utils::Direction::RIGHT);
    }
    if (action == GameController::Action::MOVE_LEFT) {
        return;
    }
}

GameController::Action GameController::getAction() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        return Action::MOVE_LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        return Action::MOVE_RIGHT;
    }

    return Action::NONE;
}

