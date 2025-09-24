//
// Created by joachimverleysen on 12/11/24.
//

#ifndef DOODLEJUMP_VISUALS_H
#define DOODLEJUMP_VISUALS_H

#include <SFML/Graphics/Texture.hpp>
#include <map>
#include "../model/entity/Entity.h"
#include "../utils/Position.h"

namespace Visuals {
    using TextureMap = std::map<EntityState, const sf::Texture*>;
    enum class AnimationState {
        IDLE,
        LEFT,
        RIGHT
    };

    Position world2SFML(const Position &position);
    Position SFML2World(const Position &position);
}

#endif //DOODLEJUMP_VISUALS_H
