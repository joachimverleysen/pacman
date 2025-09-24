#include "Renderer.h"
#include "../configure/constants.h"

Renderer::Renderer(sf::RenderWindow &window)
    : window_(window){

  sf::Texture background_texture;
  // Set file_background texture + sprite
  if (!background_texture_.loadFromFile(Config::TextureFiles::background)) {
    throw std::runtime_error("Invalid file_background path");
  }
  background_sprite_.setTexture(background_texture_);
}

void Renderer::render() {
  // window_.getSize();
  window_.clear();
  window_.draw(background_sprite_);
  renderEntities();
  window_.display();
}

void Renderer::renderEntities() {
  for (auto &view : factory_->getViews()) {
    view.lock()->render(window_);
  }
}

void Renderer::update() { render(); }

void Renderer::setFactory(std::shared_ptr<EntityViewFactory> &factory) {
    factory_ = factory;
}

