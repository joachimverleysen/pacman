#include "World.h"

#include "../configure/constants.h"
#include "utils/CollisionHandler.h"
#include "utils/Stopwatch.h"
#include <utility>

[[maybe_unused]] const std::vector<std::shared_ptr<Entity>> &
World::getEntities() const {
  return entities_;
}

void World::createPlayer(std::shared_ptr<MazeNode> node) {
  player_ = factory_.createPlayer(std::move(node));
  entities_.push_back(player_);
  notifyObservers();
}

void World::createGhost(std::shared_ptr<MazeNode> node) {
  auto ghost = factory_.createGhost(std::move(node));
  entities_.push_back(ghost);
  ghosts_.push_back(ghost);
  notifyObservers();
}

void World::placeGhosts() {
  for (auto &node : Maze::getInstance()->ghost_nodes_) {
    createGhost(node);
  }
}

void World::updateGhosts() {
  for (auto &ghost : ghosts_)
    ghost->update();
}

void World::makeWall() {
  auto grid = Maze::getInstance()->grid_;
  for (unsigned int row = 0; row < grid.size(); row++) {
    for (unsigned int column = 0; column < grid[row].size(); column++) {
      if (grid[row][column] == 'W')
        placeWall(row, column);
    }
  }
}
void World::placeWall(unsigned int row, unsigned int column) {
  auto wall = factory_.createWall(row, column);
  entities_.push_back(wall);
  notifyObservers();
}


void World::initialize() {
  cleanupEntities();

  makeWall();
  placeGhosts();
  createPlayer(Maze::getInstance()->start_node_);
  player_->update();
  updateGhosts();
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
  updateAllEntities();
}

void World::checkCollisions() {
  for (auto &entity : entities_) {
    if (entity == player_)
      continue;

    CollisionHandler::onCollision(entity.get(), player_.get());
  }
}

void World::updateAllEntities() {
  for (auto &e : entities_) {
    e->update();
  }
}
