#include "World.h"

#include "../configure/constants.h"
#include "../view/state/StateManager.h"
#include "utils/CollisionHandler.h"
#include "utils/Stopwatch.h"
#include <utility>

World::World(std::shared_ptr<AbstractFactory> factory,
             std::weak_ptr<StateManager> state_manager)
    : State(std::move(factory)), state_manager_(state_manager) {}

[[maybe_unused]] const std::vector<std::shared_ptr<Entity>> &
World::getEntities() const {
  return entities_;
}

void World::handleAction(GameAction action) {
  std::optional<Direction> direction = Utils::getDirection(action);
  if (action == GameAction::NONE or !direction)
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

void World::placeGhosts() {
  // To determine types, we simply cycle over the possible types
  int NRTYPES = 3;
  GhostType types[3] = {GhostType::Orange, GhostType::Red, GhostType::Pink};
  int timeouts[4] = {0, 0, 5, 10};
  int types_index = 0;
  int timeouts_index= 0;
  for (auto &node : Maze::getInstance()->ghost_nodes_) {
    types_index = types_index % NRTYPES;
    timeouts_index= timeouts_index % 4;
    auto ghost = factory_->createGhost(node, player_, types[types_index]);
    ghost->startTimeOut(timeouts[timeouts_index]);
    addEntity(ghost);
    types_index++;
    timeouts_index++;
  }
}

void World::placeCoins() {
  for (auto pos : Maze::getInstance()->coin_positions_) {
    auto coin = factory_->createCoin(pos);
    addEntity(coin);
  }
}

void World::placeFruits() {
  for (auto pos : Maze::getInstance()->fruit_positions_) {
    auto fruit = factory_->createFruit(pos);
    addEntity(fruit);
  }
}

void World::createWall() {
  auto positions = Maze::getInstance()->wall_positions_;
  wall_ = factory_->createWall(positions);
  entities_.push_back(wall_);
}

void World::makeDesign() {
  // Instruction to enter pause menu
  TextConfig config;
  config.text = "Press SPACE to pause";
  config.font = MyFont::LIBER;
  auto text_ = factory_->createText({0, -0.95}, config);
  entities_.push_back(text_);
}

void World::initialize() {
  try {
    verifyInit();
  } catch (std::logic_error &e) {
    std::cerr << "World initialization failed:\n";
    std::cerr << e.what() << '\n';
    exit(1);
  }
  cleanupEntities();

  // makeWall();
  makeDesign();
  createWall();
  createPlayer(Maze::getInstance()->start_node_);
  player_->setDirection(Direction::LEFT);
  placeGhosts();
  placeCoins();
  placeFruits();
  wall_->update();
}

void World::cleanupEntities() {
  cleanUpEntities(entities_);
  cleanUpEntities(coins_);
  cleanUpEntities(fruits_);
  cleanUpEntities(ghosts_);
}

void World::checkState() {
  if (!player_->isActive()) {
    gameOver();
    return;
  }
  if (coins_.empty())
    victory();
}

void World::update() {
  checkState();
  Stopwatch::getInstance()->update();
  checkCollisions();
  cleanupEntities();
  updateAllEntities();
}

void World::gameOver() {
  state_manager_.lock()->onLevelGameOver();
}

void World::victory() {
  state_manager_.lock()->onLevelGameOver();
}

bool World::verifyInit() const {
  if (!Maze::getInstance()->start_node_)
    throw std::logic_error("No start node in maze");
  return true;
}

void World::checkCollisions() {
  for (auto &entity : entities_) {
    if (entity->getType() == EntityType::Player ||
        entity->getType() == EntityType::Wall)
      continue;

    if (CollisionHandler::checkCollision(entity.get(), player_.get()))
      CollisionHandler::onCollision(entity.get(), player_.get());
  }
}

void World::updateAllEntities() {
  for (auto &e : entities_) {
    e->update();
  }
}

World::Status World::getStatus() const { return status_; }

void World::setStatus(World::Status status) { status_ = status; }
