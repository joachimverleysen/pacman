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


class World : public State {
public:
  friend GameController;
public:
  enum class Status {GAME_OVER, VICTORY, RUNNING};

private:
  Status status_{Status::RUNNING};
  std::weak_ptr<StateManager> state_manager_;
  std::shared_ptr<Player> player_;
//  std::vector<std::shared_ptr<Entity>> entities_;
  std::vector<std::shared_ptr<Entity>> ghosts_;
  std::vector<std::shared_ptr<Coin>> coins_;
  std::vector<std::vector<char>> arena_grid_;
  std::shared_ptr<MazeNode> init_node_;
  std::shared_ptr<Wall> wall_;

public:
  [[maybe_unused]] [[nodiscard]] const std::vector<std::shared_ptr<Entity>> &
  getEntities() const;
  void setStatus(Status status);
  Status getStatus() const;

public:
  World(std::shared_ptr<AbstractFactory> factory,
        std::weak_ptr<StateManager> state_manager);

  void initialize() override;

  StateNS::Type getType() const override {return StateNS::Type::WORLD;}

  void updateAllEntities();

  void update() override;

  void checkCollisions();

  void createPlayer(std::shared_ptr<MazeNode> node);

  void createGhost(std::shared_ptr<MazeNode> node);

  void createWall();

  void placeGhosts();

  void cleanupEntities();

  [[nodiscard]] bool verifyInit() const;

  void handleAction(GameAction action) override;

  void createCoin(MazePosition pos);

  void placeCoins();

  void gameOver();

  void checkState();

  void victory();

  void makeDesign();

};

#endif // WORLD_H
