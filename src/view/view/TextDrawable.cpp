#include "TextDrawable.h"

TextDrawable::TextDrawable(sf::Text &text)
: text_(text){
}

void TextDrawable::draw(sf::RenderWindow &window) {
  window.draw(text_);
}

void TextDrawable::setPosition(MyVector pos) {
 text_.setPosition(pos.x, pos.y);
}

void TextDrawable::updateState(Entity::State state) {

}

void TextDrawable::setText(const std::string &text) {
  text_.setString(text);
}
