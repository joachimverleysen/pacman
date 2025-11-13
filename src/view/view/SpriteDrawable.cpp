#include "SpriteDrawable.h"
#include "../../configure/constants.h"
#include "../Visuals.h"
#include "../../logic/utils/Stopwatch.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

SpriteDrawable::SpriteDrawable(Texture::TextureMap texture_map, float scale)
    : texture_map_(texture_map), scale_(scale),
      current_texture_(texture_map_[Entity::State::IDLE][0]) {
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
  current_texture_ = texture;
  sprite_.setTexture(*texture);
}

void SpriteDrawable::updateState(Entity::State state) {
  if (state != state_)  // Animation switch
    texture_index_ = 0;
  state_ = state;
  const sf::Texture *texture_new = texture_map_[state_][texture_index_];
  setTexture(texture_new);
  accumulated_delta_time_ += Stopwatch::getInstance()->getDeltaTime();
  if (accumulated_delta_time_ * 500 > animation_interval_) {
    accumulated_delta_time_ = 0;
    nextTexture();
  }

}


void SpriteDrawable::nextTexture() {
  auto textures = texture_map_[state_];
  texture_index_ = (texture_index_ + 1) % textures.size();
  setTexture(textures[texture_index_]);
}