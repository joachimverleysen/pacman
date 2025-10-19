#include "../logic/utils/Position.h"
#include "DrawableInterface.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window/Window.hpp>
#include <algorithm>
#include <memory>
#ifndef SHAPE_DRAWABLE_H

class ShapeDrawable : public DrawableInterface {
  std::unique_ptr<sf::Shape> shape_;

public:
  ShapeDrawable(std::unique_ptr<sf::Shape> shape) : shape_(std::move(shape)) {}
  void draw(sf::RenderWindow &window) override { window.draw(*shape_); }
  void setPosition(Position pos) override { shape_->setPosition(pos.x, pos.y); }
};
#endif // !SHAPE_DRAWABLE_H
