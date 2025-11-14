#ifndef PACMAN_TEXTDRAWABLE_H
#define PACMAN_TEXTDRAWABLE_H

#include <string>
#include <SFML/Graphics/Text.hpp>
#include "DrawableInterface.h"

class TextDrawable : public DrawableInterface {
  sf::Text text_;
public:
  TextDrawable(sf::Text &text);

  void draw(sf::RenderWindow &window) override;

  void setPosition(MyVector pos) override;

  void updateState(Entity::State state) override;
};


#endif //PACMAN_TEXTDRAWABLE_H
