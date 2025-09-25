//
// Created by joachimverleysen on 11/26/24.
//

#include "World.h"
#include "CollisionHandler.h"
#include "../configure/constants.h"

const std::vector<std::shared_ptr<Entity>> &World::getEntities() const {
  return entities_;
}
const std::vector<std::shared_ptr<Entity>> &World::getNewEntities() const {
  return new_entities_;
}

void World::createPlayer(float x, float y) {
  // todo : extract scale constant
  player_ = factory_.createPlayer();
  player_->setPosition({0, -500});
  entities_.push_back(player_);
  new_entities_.push_back(player_);
}

void World::initialize() { createPlayer(0, -500); }

Player *World::getPlayer() const { return player_.get(); }

void World::updateEntities(float delta_time) {
  // Update every entity
  for (auto &entity : entities_) {
    entity->update(delta_time);
  }

  // Remove inactive entities
//  entities_.erase(std::remove_if(entities_.begin(), entities_.end(),
//                                 [](const std::shared_ptr<Entity> &entity) {
//                                   return !entity->isActive();
//                                 }),
//                  entities_.end());
}

void World::update(float delta_time) {
  if (!player_->isActive()) {
    return;
  }
  updateEntities(delta_time);
  checkCollisions();
  new_entities_.clear();
}

void World::checkCollisions() {
  for (auto &entity : entities_) {
    if (entity == player_)
      continue;

    CollisionHandler::onCollision(entity.get(), player_.get());
  }
}

void World::checkInitialization() const {
  if (!player_)
    throw std::runtime_error("Player not initialized");
}
