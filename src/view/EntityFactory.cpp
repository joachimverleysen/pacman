#include "EntityFactory.h"
#include "../configure/constants.h"
#include "../logic/utils/Camera.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "ShapeDrawable.h"
#include "EntityView.h"
#include <SFML/System/Vector2.hpp>
#include <memory>

std::shared_ptr<Player> EntityFactory::createPlayer(NodePtr node) {
  std::shared_ptr<Player> player = std::make_shared<Player>(
      node, Config::Player::WIDTH, Config::Player::HEIGHT);
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
  views_.push_back(view);
  return player;
}

const std::vector<std::weak_ptr<EntityView>> &EntityFactory::getViews() const {
  return views_;
}

std::shared_ptr<Wall> EntityFactory::createWall(unsigned int row,
                                                unsigned int column) {
  auto maze = Maze::getInstance();
  auto wall = std::make_shared<Wall>(row, column);

  Position topleft = Camera::world2Window(wall->getPosition());

  using Config::Window::UNIT_LENGTH;
  Position bottomright = topleft + Position{UNIT_LENGTH, UNIT_LENGTH};
  float x_distance = bottomright.x - topleft.x;
  float y_distance = bottomright.y - topleft.y;
  sf::Vector2f vec{x_distance, y_distance};
  std::unique_ptr<sf::RectangleShape> rect =
      std::make_unique<sf::RectangleShape>(vec);
  sf::Color darkblue{11, 0, 200};
  rect->setFillColor(darkblue);

  rect->setPosition(topleft.x, topleft.y);

  std::unique_ptr<ShapeDrawable> drawable =
      std::move(std::make_unique<ShapeDrawable>(std::move(rect)));

  std::shared_ptr<EntityView> view =
      std::make_shared<EntityView>(wall, std::move(drawable));

  wall->addObserver(view);
  Position pos = Camera::window2World(topleft);
  wall->setPosition(pos);
  views_.push_back(view);

  return wall;
}
