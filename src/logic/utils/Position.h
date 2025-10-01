//
// Created by joachimverleysen on 12/27/24.
//

#ifndef DOODLEJUMP_POSITION_H
#define DOODLEJUMP_POSITION_H

struct Position {
    float x, y;

    Position(float x = 0, float y = 0) : x(x), y(y) {}

    Position operator+(const Position& other) const {
        return {x + other.x, y + other.y};
    }
    Position operator-(const Position& other) const {
        return {x - other.x, y - other.y};
    }

};
#endif //DOODLEJUMP_POSITION_H
