#include "World.h"

#include "../configure/constants.h"
#include "utils/CollisionHandler.h"
#include "utils/Stopwatch.h"
#include <utility>

World::World(std::unique_ptr<AbstractFactory> factory)
: State(std::move(factory)){

}

[[maybe_unused]] const std::vector<std::shared_ptr<Entity>> &
World::getEntities() const {
  return entities_;
}

void World::handleAction(Action action) {
  std::optional<Direction> direction = Utils::getDirection(action);
    if (action == Action::NONE or !direction)
    return;
  // If player does not have target, find one.
  if (player_->updateTarget(direction.value())) {
    player_->startMove();
  } else
    return;
}

void World::createPlayer(std::shared_ptr<MazeNode> node) {
  player_ = factory_->createPlayer(std::move(node));
  entities_.push_back(player_);
  notifyObservers();
}

void World::createGhost(std::shared_ptr<MazeNode> node) {
  auto ghost = factory_->createGhost(std::move(node));
  entities_.push_back(ghost);
  ghosts_.push_back(ghost);
  notifyObservers();
}

void World::placeGhosts() {
  for (auto &node : Maze::getInstance()->ghost_nodes_) {
    createGhost(node);
  }
}

void World::createWall() {
  auto positions = Maze::getInstance()->wall_positions_;
  wall_ = factory_->createWall(positions);
  entities_.push_back(wall_);
}

void World::updateGhosts() {
  for (auto &ghost : ghosts_)
    ghost->update();
}

//void World::makeWall() {
//  auto grid = Maze::getInstance()->grid_;
//  for (unsigned int row = 0; row < grid.size(); row++) {
//    for (unsigned int column = 0; column < grid[row].size(); column++) {
//      if (grid[row][column] == 'W')
//        placeWall(row, column);
//    }
//  }
//}
//void World::placeWall(unsigned int row, unsigned int column) {
//  auto wall = factory_.createWall(row, column);
//  entities_.push_back(wall);
//  notifyObservers();
//}

void World::initialize() {
  try {
    verifyInit();
  }
  catch (std::logic_error &e) {
    std::cerr << "World initialization failed:\n";
    std::cerr << e.what() << '\n';
    exit(1);
  }
  cleanupEntities();

  // makeWall();
  createWall();
  placeGhosts();
  createPlayer(Maze::getInstance()->start_node_);
//  player_->update();
  updateGhosts();
  wall_->update();
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
  Stopwatch::getInstance()->update();
  checkCollisions();
  cleanupEntities();
  updateAllEntities();
}

bool World::verifyInit() const {
  if (! Maze::getInstance()->start_node_)
    throw std::logic_error("No start node in maze");
}
void World::checkCollisions() {
  for (auto &entity : entities_) {
    if (entity->getType() == EntityType::Player ||
    entity->getType() == EntityType::Wall)
      continue;

    CollisionHandler::onCollision(entity.get(), player_.get());
  }
}

void World::updateAllEntities() {
  for (auto &e : entities_) {
    e->update();
  }
}

