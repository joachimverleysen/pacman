//
// Created by joachimverleysen on 11/26/24.
//

#include "World.h"
#include "../configure/constants.h"
#include "utils/CollisionHandler.h"
#include "utils/Stopwatch.h"

const std::vector<std::shared_ptr<Entity>> &World::getEntities() const {
  return entities_;
}
const std::vector<std::shared_ptr<Entity>> &World::getNewEntities() const {
  return new_entities_;
}

void World::createPlayer(float x, float y) {
  player_ = factory_.createPlayer();
  player_->setPosition({x, y});
  entities_.push_back(player_);
  //  new_entities_.push_back(player_);
  notifyObservers();
}

void World::createPlayer(std::shared_ptr<MazeNode> node) {
  auto maze = Maze::getInstance();
  Position pos = maze->getWorldPosition(node->row_, node->column_);
  player_ = factory_.createPlayer();
  player_->node_ = node;
  player_->setPosition(pos);
  entities_.push_back(player_);
  //  new_entities_.push_back(player_);
  notifyObservers();
}

void World::initialize() {
  //  createPlayer(20, 0);
  cleanupEntities();
  //  checkInitialization();
  //  player_->update();

  // Initialize init node
  // todo: how to determine init node?
  Position pos;
  auto maze = Maze::getInstance();
  for (auto &row : maze->node_map_) {
    for (auto &node : row) {
      if (node) {
        init_node_ = node;
        pos = maze->getWorldPosition(node->row_, node->column_);
      }
    }
  }
  createPlayer(init_node_);
  updateAllEntities();
}

Player *World::getPlayer() const { return player_.get(); }

void World::cleanupEntities() {
  for (auto &e : entities_) {
    if (!e->isActive()) {
    }
  }
  entities_.erase(std::remove_if(entities_.begin(), entities_.end(),
                                 [this](const std::shared_ptr<Entity> &entity) {
                                   // If any entity gets deactivated, notify
                                   // observers
                                   bool active = entity->isActive();
                                   if (!active)
                                     notifyObservers();
                                   return !entity->isActive();
                                 }),
                  entities_.end());
}

void World::update() {
  if (!player_->isActive()) {
    return;
  }
  cleanupEntities();
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

void World::updateAllEntities() {
  for (auto &e : entities_) {
    e->update();
  }
}
