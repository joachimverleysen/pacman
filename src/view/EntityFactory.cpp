#include "EntityFactory.h"
#include "../configure/constants.h"
#include "../logic/utils/Camera.h"
#include "view/EntityView.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "view/ShapeDrawable.h"
#include "view/WallView.h"
#include "state/StateManager.h"
#include "state/StateView.h"
#include <SFML/System/Vector2.hpp>
#include <memory>

MyVector dimensionsToWorld(float width, float height) {
  MyVector start = Camera::window2World({0, 0});
  MyVector end = Camera::window2World({width, height});
  float w = std::abs(end.x - start.x);
  float h = std::abs(end.y - start.y);
  return {w, h};
}

std::shared_ptr<Player> EntityFactory::createPlayer(NodePtr node) {
  MyVector size_dimensions =
      dimensionsToWorld(Config::Player::WIDTH, Config::Player::HEIGHT);
  float w = size_dimensions.x;
  float h = size_dimensions.y;
  std::shared_ptr<Player> player = std::make_shared<Player>(node, w, h);
  // todo: no hardcoded
  std::string type = "pacman";
  Texture::TextureMap texture_map =
      TextureParser::getTextureMap(Config::TextureFiles::sprites_json, type);

  std::unique_ptr<SpriteDrawable> drawable =
      std::make_unique<SpriteDrawable>(texture_map, Config::Player::SCALE);
  std::shared_ptr<EntityView> view = std::make_shared<EntityView>(
      player,
      std::move(drawable)); // player is passed as a weak pointer here

  player->addObserver(view); // view is passed as shared pointer here
  addView(view);
  return player;
}

void EntityFactory::addView(std::shared_ptr<EntityView> view) {
  auto &vec = state_manager_->getCurrentStateView()->views_;
  vec.push_back(view);
}
std::shared_ptr<Ghost> EntityFactory::createGhost(NodePtr node) {
  MyVector size_dimensions =
      dimensionsToWorld(Config::Ghost::WIDTH, Config::Ghost::HEIGHT);
  float w = size_dimensions.x;
  float h = size_dimensions.y;
  std::shared_ptr<Ghost> ghost = std::make_shared<Ghost>(node, w, h);
  // todo: no hardcoded
  std::string type = "ghost";
  Texture::TextureMap texture_map =
      TextureParser::getTextureMap(Config::TextureFiles::sprites_json, type);

  std::unique_ptr<SpriteDrawable> drawable =
      std::make_unique<SpriteDrawable>(texture_map, Config::Player::SCALE);
  std::shared_ptr<EntityView> view = std::make_shared<EntityView>(
      ghost,
      std::move(drawable)); // ghost is passed as a weak pointer here

  ghost->addObserver(view); // view is passed as shared pointer here
  addView(view);
  return ghost;
}

const std::vector<std::weak_ptr<EntityView>> &EntityFactory::getViews() const {
  return views_;
}

std::shared_ptr<Wall>
EntityFactory::createWall(std::vector<MazePosition> &positions) {
  using Config::Window::UNIT_LENGTH;
  std::shared_ptr<Wall> wall = std::make_shared<Wall>(positions);
  sf::Vector2f vec{UNIT_LENGTH, UNIT_LENGTH};
  std::unique_ptr<sf::RectangleShape> rect =
      std::make_unique<sf::RectangleShape>(vec);
  sf::Color darkblue{11, 0, 200};
  rect->setFillColor(darkblue);
  std::unique_ptr<ShapeDrawable> drawable =
      std::move(std::make_unique<ShapeDrawable>(std::move(rect)));

  std::shared_ptr<EntityView> view =
      std::make_shared<WallView>(wall, std::move(drawable));

  wall->addObserver(view);
  addView(view);
  return wall;
}

