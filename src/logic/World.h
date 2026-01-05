#ifndef WORLD_H
#define WORLD_H

#include "../configure/constants.h"
#include "../view/EntityFactory.h"
#include "../view/view/EntityView.h"
#include "Score.h"
#include "entity/Player.h"
#include "maze/Maze.h"
#include "state/State.h"
#include "utils/Utils.h"
#include <memory>
#include <string>

#include "utils/AbstractDispatcher.h"
#include "utils/Visitor.h"

class AbstractDispatcher;
using Seconds = float;

class World : public State, public Visitor {
public:
  World(std::shared_ptr<AbstractFactory> factory,
        std::shared_ptr<AbstractDispatcher> dispatcher,
        std::weak_ptr<StateManager> state_manager, unsigned int difficulty,
        unsigned int &lives_remaining);

  friend GameController;

public:
  // Gameplay
private:
  float ghost_speed_{150};
  unsigned int difficulty_;
  unsigned int &lives_remaining_;
  bool frightened_ghosts_{false};
  bool freeze_{false};

private:
  std::weak_ptr<StateManager> state_manager_;
  std::shared_ptr<Player> player_;
  std::vector<std::shared_ptr<Ghost>> ghosts_;
  std::vector<std::shared_ptr<Coin>> coins_;
  std::vector<std::shared_ptr<Fruit>> fruits_;
  std::vector<std::vector<char>> arena_grid_;
  std::shared_ptr<MazeNode> player_start_node_;
  std::shared_ptr<Wall> wall_;
  std::shared_ptr<Text> score_display_;

private:
  Seconds frightened_ghosts_duration_{Config::Ghost::FRIGHTENED_DURATION};
  std::shared_ptr<Timer> frightened_ghosts_timer_{nullptr};
  std::shared_ptr<Timer> freeze_timer_{nullptr};

public:
  /// Removes inactive entities
  template <typename EntityT>
  void
  cleanUpEntities(std::vector<std::shared_ptr<EntityT>> &entity_container) {
    entity_container.erase(
        std::remove_if(entity_container.begin(), entity_container.end(),
                       [this](const std::shared_ptr<EntityT> &entity) {
                         return !entity->isActive();
                       }),
        entity_container.end());
  }

  template <typename EntityT> void addEntity(std::shared_ptr<EntityT> entity) {
    entities_.push_back(entity);
    if constexpr (std::is_same_v<EntityT, Ghost>)
      ghosts_.push_back(entity);
    if constexpr (std::is_same_v<EntityT, Fruit>)
      fruits_.push_back(entity);
    if constexpr (std::is_same_v<EntityT, Coin>)
      coins_.push_back(entity);
  }

public:
  /// Returns all active entities
  [[maybe_unused]] [[nodiscard]] const std::vector<std::shared_ptr<Entity>> &
  getEntities() const;

  // Init
public:
  void initialize() override;

  /// Makes the design (text, score etc.)
  void makeDesign();

  /// Creates player at given node
  void createPlayer(std::shared_ptr<MazeNode> node);

  /// Creates all wall units
  void createWall();

  /// Displays the score
  void displayScore();

  /// Places the ghosts according to the maze layout
  void placeGhosts();

  /// Checks if world is properly initialized
  [[nodiscard]] bool verifyInit() const;

  /// Places the coins according to the maze layout
  void placeCoins();

  /// Puts ghosts in frightened mode and starts timer
  void frightenGhosts();

  /// Unfrightens ghosts (back to chase mode)
  void unfrightenGhosts();

  /// Handles an action
  void handleAction(GameAction action) override;

  void visit(FruitEatenEvent &event) override;
  void visit(CoinEatenEvent &event) override;
  void visit(GhostEatenEvent &event) override;
  void visit(FrightenGhostsEvent &event) override;
  void visit(PacmanDiesEvent &event) override;
  void visit(NewLevelEvent &event) override;

  void cleanupEntities();

  /// Removes all ghosts from world
  void removeGhosts();

  /// Removes player
  void removePlayer();

  /// On game over
  void gameOver();

  /// Checks if current state results in victory/gameover/death/end of
  /// frightened
  void checkState();

  /// Checks all entity collisions and handles them
  void checkPlayerCollisions();

  void updateAllEntities();

  void update() override;

  /// Freezes the screen
  void freeze(int seconds);

  /// Continues the level by resetting player's and ghost's positions
  void continueLevel();

  /// On victory
  void victory();

  /// Places fruits according to the maze layout
  void placeFruits();

  StateNS::Type getType() const override { return StateNS::Type::WORLD; }

  /// Applies difficulty to world settings
  void applyDifficulty(int difficulty);
};

#endif // WORLD_H
