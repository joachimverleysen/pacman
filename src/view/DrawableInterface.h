#include "../logic/entity/Entity.h"
#include "../logic/utils/Position.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#ifndef DRAWABLE_INTERFACE_H

class DrawableInterface {
protected:
  Entity::State state_;

public:
  virtual void draw(sf::RenderWindow &window) = 0;
  virtual void setPosition(Position pos) = 0;
  virtual void updateState(Entity::State state) = 0;
  virtual ~DrawableInterface() = default;
};
#endif // !DRAWABLE_INTERFACE_H
