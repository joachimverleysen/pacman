//
// Created by joachimverleysen on 12/11/24.
//

#ifndef DOODLEJUMP_VISUALS_H
#define DOODLEJUMP_VISUALS_H

#include "../logic/entity/Entity.h"
#include "../logic/utils/Position.h"
#include <SFML/Graphics/Texture.hpp>
#include <map>

namespace Texture {
using TextureMap = std::map<PacmanState, const sf::Texture *>;
enum class AnimationState { IDLE, LEFT, RIGHT };

} // namespace Texture

namespace Camera {
Position world2SFML(const Position &position);
Position SFML2World(const Position &position);
} // namespace Camera

#endif // DOODLEJUMP_VISUALS_H
