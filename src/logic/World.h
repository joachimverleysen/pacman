#ifndef WORLD_H
#define WORLD_H

#include "utils/Utils.h"
#include "../configure/constants.h"
#include "../view/EntityFactory.h"
#include "../view/view/EntityView.h"
#include "State.h"
#include "entity/Player.h"
#include "maze/Maze.h"
#include <memory>
#include <string>

using Seconds = float;

class World : public State {
public:
  friend GameController;
public:
  enum class Status {GAME_OVER, VICTORY, RUNNING};

private:
  Status status_{Status::RUNNING};
  std::weak_ptr<StateManager> state_manager_;
  std::shared_ptr<Player> player_;
  std::vector<std::shared_ptr<Ghost>> ghosts_;
  std::vector<std::shared_ptr<Coin>> coins_;
  std::vector<std::shared_ptr<Fruit>> fruits_;
  std::vector<std::vector<char>> arena_grid_;
  std::shared_ptr<MazeNode> init_node_;
  std::shared_ptr<Wall> wall_;

private:
  Seconds freightened_ghosts_duration_{5};
  std::shared_ptr<Timer> frightened_ghosts_timer_{nullptr};

public:
  template<typename EntityT>
  void cleanUpEntities(std::vector<std::shared_ptr<EntityT>> &entity_container) {
    entity_container.erase(std::remove_if(entity_container.begin(), entity_container.end(),
                                          [this](const std::shared_ptr<EntityT> &entity) {
                                            bool active = entity->isActive();
                                            if (!active)
                                              notifyObservers();
                                            return !entity->isActive();
    }),
                           entity_container.end());

  }

  template<typename EntityT>
  void addEntity(std::shared_ptr<EntityT> entity) {
    entities_.push_back(entity);
    if constexpr (std::is_same_v<EntityT, Ghost>)
      ghosts_.push_back(entity);
    if constexpr (std::is_same_v<EntityT, Fruit>)
      fruits_.push_back(entity);
    if constexpr (std::is_same_v<EntityT, Coin>)
      coins_.push_back(entity);
  }

public:
  [[maybe_unused]] [[nodiscard]] const std::vector<std::shared_ptr<Entity>> &
  getEntities() const;
  void setStatus(Status status);
  Status getStatus() const;

  /// Init  ///
public:
  World(std::shared_ptr<AbstractFactory> factory, std::weak_ptr<StateManager> state_manager,
        unsigned int difficulty);

  void initialize() override;


  void makeDesign();

  void createPlayer(std::shared_ptr<MazeNode> node);

  void createWall();

  void placeGhosts();


  [[nodiscard]] bool verifyInit() const;


  void placeCoins();

  /// Update ///

  void frightenGhosts();

  void unfrightenGhosts();

  void handleAction(GameAction action) override;

  void cleanupEntities();

  void gameOver();

  void checkState();

  void checkCollisions();

  void updateAllEntities();

  void update() override;

  void victory();

  void placeFruits();

  void placeGhostsFixedType(GhostType type);

  StateNS::Type getType() const override {return StateNS::Type::WORLD;}

};

#endif // WORLD_H
