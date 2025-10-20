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
  // player_ = factory_.createPlayer();
  player_->setPosition({x, y});
  entities_.push_back(player_);
  //  new_entities_.push_back(player_);
  notifyObservers();
}

void World::createPlayer(std::shared_ptr<MazeNode> node) {
  player_ = factory_.createPlayer(node);
  entities_.push_back(player_);
  //  new_entities_.push_back(player_);
  notifyObservers();
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
        pos = node->getPosition();
      }
    }
  }
  makeWall();
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
  player_->update();
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
