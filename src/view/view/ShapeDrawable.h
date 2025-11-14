#ifndef SHAPE_DRAWABLE_H
#define SHAPE_DRAWABLE_H
#include "../../logic/utils/MyVector.h"
#include "DrawableInterface.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window/Window.hpp>
#include <algorithm>
#include <memory>

class ShapeDrawable : public DrawableInterface {

  std::unique_ptr<sf::Shape> shape_;

public:
  ShapeDrawable(std::unique_ptr<sf::Shape> shape);
  ShapeDrawable(std::unique_ptr<sf::Shape> shape, MyVector pos);
  void draw(sf::RenderWindow &window) override;
  void setPosition(MyVector pos) override;
  void updateState(Entity::State) override{};
};
#endif // !SHAPE_DRAWABLE_H
