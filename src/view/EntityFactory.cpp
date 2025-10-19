#include "EntityFactory.h"
#include "../configure/constants.h"
#include "EntityView.h"

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
