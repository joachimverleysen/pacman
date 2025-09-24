//
// Created by joachimverleysen on 12/11/24.
//
#include "Visuals.h"

Position Visuals::world2SFML(const Position &position) {
    return {position.x, -position.y};
}

Position Visuals::SFML2World(const Position &position) {
    return {position.x, -position.y};

}

