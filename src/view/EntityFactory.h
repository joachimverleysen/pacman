#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "../logic/entity/AbstractFactory.h"
#include "../logic/entity/Player.h"
#include "../logic/utils/JSONParser.h"
#include "../logic/utils/json.hpp"
#include "view/EntityView.h"
#include "../view/TextureParser.h"
#include <SFML/Window/Window.hpp>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
// #include "Game.h"

class Game;
using json = nlohmann::json;

class StateManager;
class EntityFactory : public AbstractFactory {
  sf::RenderWindow &window_;
  Game &game_;
  std::vector<std::weak_ptr<EntityView>> views_;
  std::shared_ptr<StateManager> state_manager_;

public:
  EntityFactory() = delete;
  explicit EntityFactory(Game &game, sf::RenderWindow &window, std::shared_ptr<StateManager> state_manager)
      : game_(game), window_(window), state_manager_(state_manager) {}


  std::shared_ptr<Player> createPlayer(NodePtr) override;
  /* std::shared_ptr<Wall> createWall(unsigned int row,
                                   unsigned int column) override; */
  std::shared_ptr<Wall>
  createWall(std::vector<MazePosition> &positions) override;
  std::shared_ptr<Ghost> createGhost(NodePtr node, std::shared_ptr<Player> player) override;

  std::shared_ptr<Coin> createCoin(MazePosition pos) override;

  const std::vector<std::weak_ptr<EntityView>> &getViews() const;

  friend class Renderer;


  void addView(std::shared_ptr<EntityView> view);
};

#endif // ENTITY_FACTORY_H
