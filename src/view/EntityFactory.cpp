#include "EntityFactory.h"
#include "../configure/constants.h"

std::shared_ptr<Player> EntityFactory::createPlayer() {
  std::shared_ptr<Player> player = std::make_shared<Player>(
      Config::Player::WIDTH, Config::Player::HEIGHT, Config::Player::SCALE);
  // todo: no hardcoded
  std::string type = "pacman";
  Texture::TextureMap texture_map =
      TextureParser::getTextureMap(Config::TextureFiles::sprites_json, type);
  std::shared_ptr<EntityView> view = std::make_shared<EntityView>(
      player, texture_map, window_); // view is passed as a weak pointer here

  player->addObserver(view); // view is passed as shared pointer here
  views_.push_back(view);
  return player;
}

const std::vector<std::weak_ptr<EntityView>> &EntityFactory::getViews() const {
  return views_;
}
