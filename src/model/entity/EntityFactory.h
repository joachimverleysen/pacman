//
// Created by joachimverleysen on 12/3/24.
//
#ifndef DOODLEJUMP_ENTITYFACTORY_H
#define DOODLEJUMP_ENTITYFACTORY_H

#include "AbstractFactory.h"
#include "Player.h"
#include "../../utils/JSONParser.h"
#include "../../utils/json.hpp"
#include "../../view/EntityView.h"
#include "../../view/TextureParser.h"
#include <memory>
#include <stdexcept>
#include <string>
// #include "Game.h"

class Game;
using json = nlohmann::json;

class EntityFactory : public AbstractFactory {
  Game &game_;

public:
  EntityFactory() = default;
  explicit EntityFactory(Game &game)
      : game_(game) {
  }

  std::shared_ptr<Player> createPlayer(float x, float y, float speed) override;
};

#endif // DOODLEJUMP_ENTITYFACTORY_H
