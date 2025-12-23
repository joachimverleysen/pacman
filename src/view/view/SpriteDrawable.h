#ifndef SPRITE_DRAWABLE_H
#include "../../logic/utils/MyVector.h"
#include "../graphics/Visuals.h"
#include "DrawableInterface.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>

class SpriteDrawable : public DrawableInterface {
  sf::Sprite sprite_;
  Texture::TextureMap texture_map_;
  Texture::StateTextures state_textures_;
  unsigned int texture_index_{0};
  const sf::Texture *current_texture_;
  float scale_;
  float animation_interval_{50};
  float accumulated_delta_time_{0};

public:
  SpriteDrawable(Texture::StateTextures state_textures, float scale);
  SpriteDrawable(Texture::TextureMap texture_map, float scale);
  void draw(sf::RenderWindow &window) override;
  void setPosition(MyVector pos) override;
  void setTexture(const sf::Texture *texture);
  void updateState(Entity::State state) override;

  void nextTexture();

  void updateMode(Entity::Mode mode) override;

  void update();
};
#endif // !SPRITE_DRAWABLE_H
