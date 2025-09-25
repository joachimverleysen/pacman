//
// Created by joachimverleysen on 12/3/24.
//
#ifndef DOODLEJUMP_ENTITYFACTORY_H
#define DOODLEJUMP_ENTITYFACTORY_H

#include "../model/entity/AbstractFactory.h"
#include "../model/entity/Player.h"
#include "../utils/JSONParser.h"
#include "../utils/json.hpp"
#include "../view/EntityView.h"
#include "../view/TextureParser.h"
#include <SFML/Window/Window.hpp>
#include <memory>
#include <stdexcept>
#include <string>
// #include "Game.h"

class Game;
using json = nlohmann::json;

class EntityFactory : public AbstractFactory {
  sf::RenderWindow &window_;
  Game &game_;

public:
  EntityFactory() = delete;
  explicit EntityFactory(Game &game, sf::RenderWindow &window)
      : game_(game), window_(window) {}

  std::shared_ptr<Player> createPlayer() override;
};

#endif // DOODLEJUMP_ENTITYFACTORY_H
