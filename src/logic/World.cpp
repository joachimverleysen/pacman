#include "World.h"
#include "observer/Event.h"

#include "../configure/constants.h"
#include "../view/state/StateManager.h"
#include "utils/CollisionHandler.h"
#include "utils/Stopwatch.h"
#include "Leaderboard.h"
#include <utility>

World::World(std::shared_ptr<AbstractFactory> factory,
             std::weak_ptr<StateManager> state_manager, unsigned int difficulty)
    : State(std::move(factory)),
      state_manager_(state_manager),
      difficulty_(difficulty)
      {
  applyDifficulty(difficulty);
}

[[maybe_unused]] const std::vector<std::shared_ptr<Entity>> &
World::getEntities() const {
  return entities_;
}

void World::handleAction(GameAction action) {
  // Debug purposes
  if (action == GameAction::VICTORY)
    victory();

  // "action = player movement" case
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

void World::placeGhostsFixedType(GhostType type) {
  // To determine types, we simply cycle over the possible types
  int NR_GHOSTS = 4;
  int timeouts[4] = {0, 0, 5, 10};
  int types_index = 0;
  int timeouts_index = 0;
  for (auto &node : Maze::getInstance()->ghost_nodes_) {
    types_index = types_index % NR_GHOSTS;
    timeouts_index = timeouts_index % 4;
    auto ghost = factory_->createGhost(node, player_, type);
    ghost->startTimeOut(timeouts[timeouts_index]);
    addEntity(ghost);
    types_index++;
    timeouts_index++;
  }
}

void World::placeGhosts() {
  int NR_GHOSTS = 4;
  GhostType types[4] = {GhostType::Red, GhostType::Orange, GhostType::Pink,
                        GhostType::Pink};
  int timeouts[4] = {0, 0, 5, 10};
  int types_index = 0;
  int timeouts_index = 0;
  for (auto &node : Maze::getInstance()->ghost_nodes_) {
    types_index = types_index % NR_GHOSTS;
    timeouts_index = timeouts_index % 4;
    auto ghost = factory_->createGhost(node, player_, types[types_index]);
    ghost->startTimeOut(timeouts[timeouts_index]);
    ghost->setSpeed(ghost_speed_);
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

// todo: score should be created elsewhere.
// display should be attached to that score here.
// Only display belongs to world, not score
void World::createScore() {
  TextConfig config;
  config.text = "Score: 0";
  config.font = MyFont::LIBER;
  score_display_= factory_->createText({0.5, 0.95}, config);
}

void World::makeDesign() {
  // Press SPACE to pause
  TextConfig config;
  config.text = "Press SPACE to pause";
  config.font = MyFont::LIBER;
  auto text_ = factory_->createText({0.0, -0.90}, config);
  entities_.push_back(text_);

  // Level: #
  TextConfig level_config;
  level_config.text = "Level: " + std::to_string(difficulty_-1);
  level_config.font = MyFont::LIBER;
  text_ = factory_->createText({-0.5, 0.95}, level_config);
  entities_.push_back(text_);

}

void World::applyDifficulty(int difficulty) {
  ghost_speed_ = Config::Ghost::SPEED + difficulty * (7);
  frightened_ghosts_duration_ =
    frightened_ghosts_duration_ - difficulty * 0.5;
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
  createScore();
  wall_->update();

}

void World::cleanupEntities() {
  cleanUpEntities(entities_);
  cleanUpEntities(coins_);
  cleanUpEntities(fruits_);
  cleanUpEntities(ghosts_);
}

void World::unfrightenGhosts() {
  frightened_ghosts_ = false;
  for (auto g : ghosts_)
    g->enterChaseMode();
}

void World::checkState() {
  if (!player_->isActive()) {
    gameOver();
    return;
  }
  if (coins_.empty())
    victory();
  if (frightened_ghosts_timer_ && frightened_ghosts_timer_->done()) {
    frightened_ghosts_timer_ = nullptr;
    unfrightenGhosts();
  }
}

void World::update() {
  checkState();
  Stopwatch::getInstance()->update();
  checkCollisions();
  cleanupEntities();
  updateAllEntities();
  int score = Score::getInstance()->getValue();
  score_display_->setText(std::to_string(score));
}

void World::gameOver() {
  Leaderboard::getInstance()->addScore(
    Score::getInstance()->getValue()
    );
  state_manager_.lock()->onGameOver();

}

void World::victory() { state_manager_.lock()->onVictory(); }

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

    // No collision
    if (!CollisionHandler::checkCollision(entity.get(), player_.get()))
      continue;

    // In case of collision
    CollisionHandler::onCollision(entity.get(), player_.get());

    onPlayerCollision(entity.get()->getType());

  }
}

void World::onPlayerCollision(EntityType entity_type) {
  // todo refactor
  auto score = Score::getInstance();
  switch (entity_type) {
    case (EntityType::Fruit): {
      frightenGhosts();
      auto event = FruitEatenEvent{};
      score->handle(event);
      break;
    }
    case (EntityType::Coin): {
      auto event = CoinEatenEvent{};
      score->handle(event);
      break;
    }
    case (EntityType::Ghost): {
      if (!frightened_ghosts_)
        break;
      auto event = GhostEatenEvent{};
      score->handle(event);
    }
  }
}

void World::updateAllEntities() {
  for (auto &e : entities_) {
    e->update();
  }
}

World::Status World::getStatus() const { return status_; }

void World::setStatus(World::Status status) { status_ = status; }

void World::frightenGhosts() {
  auto event = FrightenGhostsEvent{};
  Score::getInstance()->handle(event);
  frightened_ghosts_ = true;
  std::shared_ptr<Timer> timer =
      Stopwatch::getInstance()->getNewTimer(frightened_ghosts_duration_);
  for (std::shared_ptr<Ghost> g : ghosts_)
    g->enterFrightenedMode(timer);
  frightened_ghosts_timer_ = timer;
}
