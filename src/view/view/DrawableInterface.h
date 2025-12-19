#ifndef DRAWABLE_INTERFACE_H
#define DRAWABLE_INTERFACE_H
#include "../../logic/entity/Entity.h"
#include "../../logic/utils/MyVector.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>

class DrawableInterface {
protected:
  Entity::State state_;
  Entity::Mode mode_{Entity::Mode::NORMAL};

public:
  // todo docs
  virtual void draw(sf::RenderWindow &window) = 0;
  virtual void setPosition(MyVector pos) = 0;
  virtual void updateState(Entity::State state) = 0;
  virtual void updateMode(Entity::Mode mode) = 0;
  virtual ~DrawableInterface() = default;
};
#endif // !DRAWABLE_INTERFACE_H
