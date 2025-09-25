//
// Created by joachimverleysen on 11/26/24.
//

#ifndef DOODLEJUMP_GAMECONTROLLER_H
#define DOODLEJUMP_GAMECONTROLLER_H


#include "../model/World.h"

class GameController {
    enum class Action {
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_UP,
        MOVE_DOWN,
        NONE
    };

     World& game_world_;
public:
    explicit GameController(World& game_world) : game_world_(game_world) {};

    void handleInput();

    static Action getAction();
};


#endif //DOODLEJUMP_GAMECONTROLLER_H
