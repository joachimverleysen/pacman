#include "ShapeDrawable.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

ShapeDrawable::ShapeDrawable(std::unique_ptr<sf::Shape> shape)
    : shape_(std::move(shape)) {}

void ShapeDrawable::draw(sf::RenderWindow &window) {
  window.draw(*shape_);
}

void ShapeDrawable::setPosition(Position pos) {
  shape_->setPosition(pos.x, pos.y);
}
