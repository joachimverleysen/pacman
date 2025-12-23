#include "SpriteDrawable.h"
#include "../../configure/constants.h"
#include "../graphics/Visuals.h"
#include "../../logic/utils/Stopwatch.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

SpriteDrawable::SpriteDrawable(Texture::StateTextures state_textures, float scale)
    : state_textures_(state_textures), scale_(scale),
      current_texture_(state_textures_[Entity::State::IDLE][0]) {
  sprite_.setTexture(*current_texture_);
  sprite_.setScale(scale, scale);
  sf::FloatRect bounds = sprite_.getLocalBounds();
  sprite_.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

SpriteDrawable::SpriteDrawable(Texture::TextureMap texture_map, float scale)
  : texture_map_(texture_map), scale_(scale),
    state_textures_(texture_map_[Entity::Mode::NORMAL]),
    current_texture_(state_textures_[Entity::State::IDLE][0]) {
  sprite_.setTexture(*current_texture_);
  sprite_.setScale(scale, scale);
  sf::FloatRect bounds = sprite_.getLocalBounds();
  sprite_.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void SpriteDrawable::update() {
  accumulated_delta_time_ += Stopwatch::getInstance()->getDeltaTime();
  if (accumulated_delta_time_ * 500 > animation_interval_) {
    accumulated_delta_time_ = 0;
    nextTexture();
  }
}
void SpriteDrawable::draw(sf::RenderWindow &window) {
  update();
  window.draw(sprite_);
}

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
  const sf::Texture *texture_new = state_textures_[state_][texture_index_];
  setTexture(texture_new);
}

void SpriteDrawable::updateMode(Entity::Mode mode) {
  if (texture_map_.empty()) return;
  state_textures_ = texture_map_[mode];
}


void SpriteDrawable::nextTexture() {
  auto textures = state_textures_[state_];
  if (textures.empty()) return;
  texture_index_ = (texture_index_ + 1) % textures.size();
  setTexture(textures[texture_index_]);
}

