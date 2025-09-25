//
// Created by joachimverleysen on 12/11/24.
//

#ifndef DOODLEJUMP_VISUALS_H
#define DOODLEJUMP_VISUALS_H

#include <SFML/Graphics/Texture.hpp>
#include <map>
#include "../model/entity/Entity.h"
#include "../utils/Position.h"

namespace Texture {
    using TextureMap = std::map<PacmanState, const sf::Texture*>;
    enum class AnimationState {
        IDLE,
        LEFT,
        RIGHT
    };

}

namespace Camera {
Position world2SFML(const Position &position);
Position SFML2World(const Position &position);
} // namespace Camera


#endif //DOODLEJUMP_VISUALS_H
