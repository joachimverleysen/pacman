//
// Created by joachimverleysen on 11/26/24.
//

#ifndef DOODLEJUMP_ENTITYVIEW_H
#define DOODLEJUMP_ENTITYVIEW_H

#include "../model/entity/Entity.h"
#include "../model/observer/Observer.h"
#include "TextureManager.h"
#include "Visuals.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

using FilePath = std::string;

class EntityView : public Observer {
  const sf::Texture *current_texture_;
  Texture::TextureMap texture_map_;
  std::weak_ptr<Entity> entity_;
  sf::Sprite sprite_;
  sf::RenderWindow &window_;
  Position position_{};

public:
  const Position &getPosition() const;

private:
  static Position convertPosition(const Position &position);

public:
  EntityView(std::weak_ptr<Entity> entity, Texture::TextureMap texture_map,
             sf::RenderWindow &window);

  ~EntityView() override;

  void update() override;


  void updateTexture();

  virtual void draw(sf::RenderWindow &window);

  void setPosition(Position &position);

  void setTexture(const sf::Texture *texture);

  std::shared_ptr<Entity> getEntity() const;

  void updatePosition();
};

#endif // DOODLEJUMP_ENTITYVIEW_H
