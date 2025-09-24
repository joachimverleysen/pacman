#include "EntityViewFactory.h"
#include "../configure/constants.h"
#include "../model/entity/EntityType.h"
#include "EntityView.h"
#include "TextureParser.h"
#include "Visuals.h"
#include <memory>

void EntityViewFactory::createEntityView(std::weak_ptr<Entity> entity) {
  // todo: no hardcoded type. use mapping entitytype->string
  std::string type = "player-soccer";
  Visuals::TextureMap texture_map =
      TextureParser::getTextureMap(Config::TextureFiles::sprites_json, type);
  std::shared_ptr<EntityView> view = std::make_shared<EntityView>(
      entity, texture_map); // view is passed as a weak pointer here

  entity.lock()->addObserver(view); // view is passed as shared pointer here
  views_.push_back(view);
};

void EntityViewFactory::onAddedEntity(std::weak_ptr<Entity> entity) {
  if (entity.lock()->getType() == EntityType::Player) {
    createEntityView(entity);
  }
}

const std::vector<std::weak_ptr<EntityView>> &
EntityViewFactory::getViews() const {
  return views_;
}

void EntityViewFactory::update() {
  for (auto &entity : world_.getNewEntities()) {
createEntityView(entity);
  }
}

EntityViewFactory::EntityViewFactory(World& world) : world_(world) {}
