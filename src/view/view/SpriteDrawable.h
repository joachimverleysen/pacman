#ifndef SPRITE_DRAWABLE_H
#include "../../logic/utils/MyVector.h"
#include "DrawableInterface.h"
#include "../Visuals.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>

class SpriteDrawable : public DrawableInterface {
  sf::Sprite sprite_;
  Texture::TextureMap texture_map_;
  unsigned int texture_index_{0};
  const sf::Texture *current_texture_;
  float scale_;
  float animation_interval_{90};
  float accumulated_delta_time_{0};

public:
  SpriteDrawable(Texture::TextureMap texture_map, float scale);
  void draw(sf::RenderWindow &window) override;
  void setPosition(MyVector pos) override;
  void setTexture(const sf::Texture *texture);
  void updateState(Entity::State state) override;

  void nextTexture();

};
#endif // !SPRITE_DRAWABLE_H
