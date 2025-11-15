#include "EntityFactory.h"
#include "../logic/utils/Camera.h"
#include "view/EntityView.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "view/ShapeDrawable.h"
#include "view/WallView.h"
#include "FontManager.h"
#include "state/StateManager.h"
#include "state/StateView.h"
#include "view/TextDrawable.h"
#include <memory>

MyVector dimensionsToWorld(float width, float height) {
  MyVector start = Camera::window2World({0, 0});
  MyVector end = Camera::window2World({width, height});
  float w = std::abs(end.x - start.x);
  float h = std::abs(end.y - start.y);
  return {w, h};
}


std::shared_ptr<Player> EntityFactory::createPlayer(NodePtr node) {
      MyVector dims = dimensionsToWorld(Config::Player::WIDTH, Config::Player::HEIGHT);
      return createEntityWithView<Player, EntityView>(nullptr, node, dims.x, dims.y);
  }

  std::shared_ptr<Ghost> EntityFactory::createGhost(NodePtr node, std::shared_ptr<Player> player) {
      MyVector dims = dimensionsToWorld(Config::Ghost::WIDTH, Config::Ghost::HEIGHT);
      auto ghost = EntityFactory::createEntityWithView<Ghost, EntityView>(
        [](std::shared_ptr<EntityView> view){ view->pushToForeground(); },
        node, dims.x, dims.y, player);
      return ghost;
  }

  std::shared_ptr<Wall> EntityFactory::createWall(std::vector<MazePosition>& positions) {
      return EntityFactory::createEntityWithView<Wall, WallView>(nullptr, positions);
  }

  std::shared_ptr<Coin> EntityFactory::createCoin(MazePosition pos) {
      return EntityFactory::createEntityWithView<Coin, EntityView>(nullptr, pos);
  }

void EntityFactory::addView(const std::shared_ptr<EntityView>& view) {
  auto &vec = state_manager_.lock()->getCurrentStateView()->views_;
  vec.push_back(view);
}

sf::Color getColor(Color color) {
  sf::Color result = {static_cast<sf::Uint8>(color.r),
                             static_cast<sf::Uint8>(color.b),
                             static_cast<sf::Uint8>(color.b)
  };
  return result;
}

std::shared_ptr<Text>
EntityFactory::createText(MyVector vec, TextConfig &config) {
  std::shared_ptr<Text> text = std::make_shared<Text>(config.text);
  text->setPosition(vec);
  auto font = FontManager::get(config.font);

  sf::Text text_;
  text_.setCharacterSize(config.character_size);
  text_.setStyle(sf::Text::Regular);
  text_.setFont(*font);
  text_.setString(config.text);
  sf::Color fill_color = getColor(config.fill_color);
  sf::Color outline_color = getColor(config.outline_color);
  text_.setFillColor(fill_color);
  text_.setOutlineThickness(config.outline_thickness);
  text_.setOutlineColor(outline_color);
  sf::FloatRect rc = text_.getLocalBounds();
text_.setOrigin(rc.width/2, rc.height/2);
  std::unique_ptr<TextDrawable> drawable = std::make_unique<TextDrawable>(text_);
  drawable->setPosition(Camera::world2Window(vec));
  std::shared_ptr<EntityView> text_view = std::make_shared<EntityView>(text, std::move(drawable));
  text_view->pushToForeground();
  text->addObserver(text_view);
  addView(text_view);
  return text;
}

