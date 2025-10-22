#ifndef WORLD_H
#define WORLD_H

#include "../configure/constants.h"
#include "../view/EntityFactory.h"
#include "../view/EntityView.h"
#include "entity/Player.h"
#include "maze/Maze.h"
#include <memory>
#include <string>

class World : public Subject {
public:
  friend GameController;

private:
  std::shared_ptr<Player> player_;
  std::vector<std::shared_ptr<Entity>> entities_;
  std::vector<std::shared_ptr<Entity>> ghosts_;
  EntityFactory &factory_;
  std::vector<std::vector<char>> arena_grid_;
  std::shared_ptr<MazeNode> init_node_;

public:
  [[maybe_unused]] [[nodiscard]] const std::vector<std::shared_ptr<Entity>> &
  getEntities() const;

public:
  explicit World(EntityFactory &factory) : factory_(factory) {};

  void initialize();

  void updateAllEntities();

  [[nodiscard]] Player *getPlayer() const;

  void update();

  void checkCollisions();

  void createPlayer(std::shared_ptr<MazeNode> node);

  void createGhost(std::shared_ptr<MazeNode> node);

  void placeGhosts();

  void cleanupEntities();

  void placeWall(unsigned int row, unsigned int column);

  void makeWall();

  void updateGhosts();
};

#endif // WORLD_H
