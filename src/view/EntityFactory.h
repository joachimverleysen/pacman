#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "../logic/entity/AbstractFactory.h"
#include "../logic/entity/Player.h"
#include "../logic/utils/JSONParser.h"
#include "../logic/utils/json.hpp"
#include "../view/EntityView.h"
#include "../view/TextureParser.h"
#include <SFML/Window/Window.hpp>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
// #include "Game.h"

class Game;
using json = nlohmann::json;

class EntityFactory : public AbstractFactory {
  sf::RenderWindow &window_;
  Game &game_;
  std::vector<std::weak_ptr<EntityView>> views_;

public:
  EntityFactory() = delete;
  explicit EntityFactory(Game &game, sf::RenderWindow &window)
      : game_(game), window_(window) {}

  std::shared_ptr<Player> createPlayer(NodePtr) override;
  std::shared_ptr<Wall> createWall(unsigned int row,
                                   unsigned int column) override;
  std::shared_ptr<Ghost> createGhost(NodePtr node) override;

  const std::vector<std::weak_ptr<EntityView>> &getViews() const;

  friend class Renderer;
};

#endif // ENTITY_FACTORY_H
