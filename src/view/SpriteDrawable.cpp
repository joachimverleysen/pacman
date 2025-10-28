#include "SpriteDrawable.h"
#include "../configure/constants.h"
#include "Visuals.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

SpriteDrawable::SpriteDrawable(Texture::TextureMap texture_map, float scale)
    : texture_map_(texture_map), scale_(scale),
      current_texture_(texture_map_[Entity::State::IDLE]) {
  sprite_.setTexture(*current_texture_);
  sprite_.setScale(scale, scale);
  sf::FloatRect bounds = sprite_.getLocalBounds();
  sprite_.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}
void SpriteDrawable::draw(sf::RenderWindow &window) { window.draw(sprite_); }

void SpriteDrawable::setPosition(MyVector pos) {
  sprite_.setPosition(pos.x, pos.y);
}

void SpriteDrawable::setTexture(const sf::Texture *texture) {
  sprite_.setTexture(*texture);
}

void SpriteDrawable::updateState(Entity::State state) {
  state_ = state;
  const sf::Texture *texture_new = texture_map_[state_];
  setTexture(texture_new);
}
