#include "EntityView.h"
#include "../../logic/entity/Entity.h"
#include "../../logic/utils/Camera.h"
#include "../Game.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>

EntityView::EntityView(std::weak_ptr<Entity> entity,
                       std::unique_ptr<DrawableInterface> drawable)
    : entity_(entity), drawable_(std::move(drawable)),
    position_(Camera::world2Window(entity.lock()->getPosition())) {
  drawable_->setPosition(position_);
}
EntityView::~EntityView() {
}

void EntityView::draw(sf::RenderWindow &window) { drawable_->draw(window); }

void EntityView::setPosition(MyVector &position) {
  position_ = position;
  drawable_->setPosition(position);
}

void EntityView::update() {
  drawable_->updateState(entity_.lock()->getCurrentState());
  drawable_->updateMode(entity_.lock()->getMode());
  updatePosition();
}

void EntityView::updatePosition() {
  auto entity_position = entity_.lock()->getPosition();
  auto SFML_position = Camera::world2Window(entity_position);
  drawable_->setPosition(SFML_position);
}



const MyVector &EntityView::getPosition() const { return position_; }

void EntityView::pushToForeground() {
foreground_ = true;
}

bool EntityView::isForeGround() const {
  return foreground_;
}