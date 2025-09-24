//
// Created by joachimverleysen on 11/26/24.
//

#include "EntityView.h"

#include "Game.h"
#include <memory>
#include <utility>

EntityView::EntityView(std::weak_ptr<Entity> entity,
                       Visuals::TextureMap texture_map)
    : texture_map_(texture_map), entity_(entity),
      current_texture_(texture_map[EntityState::IDLE]) {
  position_ = convertPosition(entity.lock()->getPosition());
  sprite_.setTexture(*current_texture_);
}

EntityView::~EntityView() {
  //    std::cout << "view destruct \n";
  // entity_.removeObserver(this);
}

void EntityView::setPosition(Position &position) {
  position_ = position;
  sprite_.setPosition(position.x, position.y);
}

void EntityView::update() {
  updatePosition();
  updateTexture();
}

void EntityView::updatePosition() {
  auto entity_position = entity_.lock()->getPosition();
  auto SFML_position = Visuals::world2SFML(entity_position);
  setPosition(SFML_position);
}

void EntityView::render(sf::RenderWindow &window) { window.draw(sprite_); }

void EntityView::setTexture(const sf::Texture *texture) {
  sprite_.setTexture(*texture);
}

Position EntityView::convertPosition(const Position &position) {
  return {position.x, position.y};
}

const Position &EntityView::getPosition() const { return position_; }

void EntityView::updateTexture() {
  EntityState state = entity_.lock()->getCurrentState();
  const sf::Texture *texture_new = texture_map_[state];
  setTexture(texture_new);
}

std::shared_ptr<Entity> EntityView::getEntity() const { return entity_.lock(); }
