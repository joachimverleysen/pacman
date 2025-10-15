//
// Created by joachimverleysen on 11/26/24.
//

#include "EntityView.h"

#include "../logic/entity/Entity.h"
#include "Camera.h"
#include "Game.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>

EntityView::EntityView(std::weak_ptr<Entity> entity,
                       Texture::TextureMap texture_map,
                       sf::RenderWindow &window)
    : texture_map_(texture_map), entity_(entity),
      current_texture_(texture_map[Entity::State::IDLE]), window_(window) {

  position_ = convertPosition(entity.lock()->getPosition());
  sprite_.setTexture(*current_texture_);
  sprite_.setScale(entity_.lock()->getScale(), entity_.lock()->getScale());
  sf::FloatRect bounds = sprite_.getLocalBounds();
  sprite_.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
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
  auto SFML_position = Camera::world2SFML(entity_position);
  setPosition(SFML_position);
}

void EntityView::draw(sf::RenderWindow &window) { window.draw(sprite_); }

void EntityView::setTexture(const sf::Texture *texture) {
  sprite_.setTexture(*texture);
}

Position EntityView::convertPosition(const Position &position) {
  return {position.x, position.y};
}

const Position &EntityView::getPosition() const { return position_; }

void EntityView::updateTexture() {
  Entity::State state = entity_.lock()->getCurrentState();
  const sf::Texture *texture_new = texture_map_[state];
  setTexture(texture_new);
}

std::shared_ptr<Entity> EntityView::getEntity() const { return entity_.lock(); }
