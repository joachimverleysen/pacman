#ifndef VISUALS_H
#define VISUALS_H
#include <list>

#include "../logic/entity/Entity.h"
#include "../logic/utils/MyVector.h"
#include <SFML/Graphics/Texture.hpp>
#include <map>

namespace Texture {
using TextureMap = std::map<Entity::State, std::vector<const sf::Texture *>>;
enum class AnimationState { IDLE, LEFT, RIGHT };

} // namespace Texture

#endif // VISUALS_H
