#include "EntityView.h"
#include "../logic/entity/Entity.h"
#include "../logic/utils/Camera.h"
#include "Game.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>

EntityView::EntityView(std::weak_ptr<Entity> entity,
                       std::unique_ptr<SpriteDrawable> drawable)
    : entity_(entity), drawable_(std::move(drawable)) {}
EntityView::~EntityView() {
  //    std::cout << "view destruct \n";
  // entity_.removeObserver(this);
}

void EntityView::draw(sf::RenderWindow &window) { drawable_->draw(window); }

void EntityView::setPosition(Position &position) {
  position_ = position;
  drawable_->setPosition(position);
}

void EntityView::update() {
  drawable_->updateState(entity_.lock()->getCurrentState());
  updatePosition();
  // updateTexture();
}

void EntityView::updatePosition() {
  auto entity_position = entity_.lock()->getPosition();
  auto SFML_position = Camera::world2Window(entity_position);
  drawable_->setPosition(SFML_position);
}



const Position &EntityView::getPosition() const { return position_; }
