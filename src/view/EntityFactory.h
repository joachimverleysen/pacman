#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "../logic/entity/AbstractFactory.h"
#include "../logic/entity/Fruit.h"
#include "../logic/entity/Player.h"
#include "../logic/utils/JSONParser.h"
#include "../logic/utils/TextConfig.h"
#include "../logic/utils/json.hpp"
#include "../view/TextureParser.h"
#include "view/EntityView.h"
#include "view/ShapeDrawable.h"
#include <SFML/Window/Window.hpp>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

typedef Ghost::GhostType GhostType;
class Game;
using json = nlohmann::json;

class StateManager;
class EntityFactory : public AbstractFactory {
  std::weak_ptr<StateManager> state_manager_;

public:
  friend class Renderer;

public:
  EntityFactory() = delete;
  explicit EntityFactory(std::weak_ptr<StateManager> state_manager)
      : state_manager_(state_manager) {}

  // Layout
  std::shared_ptr<Text> createText(MyVector vec, TextConfig &config);

  // Entity
  std::shared_ptr<Player> createPlayer(NodePtr) override;

  std::shared_ptr<Wall>
  createWall(std::vector<MazePosition> &positions) override;

  std::shared_ptr<Ghost> createGhost(NodePtr node,
                                     std::shared_ptr<Player> player,
                                     GhostType type) override;

  std::shared_ptr<Coin> createCoin(MazePosition pos) override;

  std::shared_ptr<Fruit> createFruit(MazePosition pos) override;

  void addView(const std::shared_ptr<EntityView> &view);

  template <typename EntityT, typename ViewT, typename... Args>
  std::shared_ptr<EntityT> createEntityWithView(Args &&...args) {
    std::shared_ptr<EntityT> entity =
        std::make_shared<EntityT>(std::forward<Args>(args)...);
    std::unique_ptr<DrawableInterface> drawable = createDrawableFor<EntityT>();
    std::shared_ptr<ViewT> view =
        std::make_shared<ViewT>(entity, std::move(drawable));

    entity->addObserver(view);
    addView(view);

    return entity;
  }

  template <typename EntityT>
  std::unique_ptr<DrawableInterface> createDrawableFor();
};

template <>
inline std::unique_ptr<DrawableInterface>
EntityFactory::createDrawableFor<Player>() {
  std::string type = "pacman";
  auto texture_map =
      TextureParser::getStateTextures(Config::TextureFiles::sprites_json, type);
  return std::make_unique<SpriteDrawable>(texture_map, Config::Player::SCALE);
}

template <>
inline std::unique_ptr<DrawableInterface>
EntityFactory::createDrawableFor<Ghost>() {
  std::string type = "ghost-pink";
  auto texture_map =
      TextureParser::getStateTextures(Config::TextureFiles::sprites_json, type);
  return std::make_unique<SpriteDrawable>(texture_map, Config::Player::SCALE);
}

template <>
inline std::unique_ptr<DrawableInterface>
EntityFactory::createDrawableFor<Wall>() {
  using Config::Window::CELL_WIDTH;
  sf::Vector2f vec{CELL_WIDTH, CELL_WIDTH};
  auto rect = std::make_unique<sf::RectangleShape>(vec);
  rect->setFillColor({11, 0, 200});
  return std::make_unique<ShapeDrawable>(std::move(rect));
}

template <>
inline std::unique_ptr<DrawableInterface>
EntityFactory::createDrawableFor<Coin>() {
  using Config::Window::CELL_WIDTH;
  auto rect = std::make_unique<sf::CircleShape>(CELL_WIDTH / 8);
  rect->setFillColor({255, 255, 0});
  return std::make_unique<ShapeDrawable>(std::move(rect));
}

template <>
inline std::unique_ptr<DrawableInterface>
EntityFactory::createDrawableFor<Fruit>() {
  auto texture_map = TextureParser::getStateTextures(
      Config::TextureFiles::sprites_json, "fruit");
  return std::make_unique<SpriteDrawable>(texture_map,
                                          Config::Player::SCALE * 0.6);
}

#endif // ENTITY_FACTORY_H
