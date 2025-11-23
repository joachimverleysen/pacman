#ifndef VISUALS_H
#define VISUALS_H
#include <list>

#include "../logic/entity/Entity.h"
#include "../logic/utils/MyVector.h"
#include <SFML/Graphics/Texture.hpp>
#include <map>

namespace Texture {
using StateTextures = std::map<Entity::State, std::vector<const sf::Texture *>>;
using TextureMap = std::map<Entity::Mode, StateTextures>;
using Types = std::vector<std::string>;
} // namespace Texture

#endif // VISUALS_H
