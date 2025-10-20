#ifndef DOODLEJUMP_WORLD_H
#define DOODLEJUMP_WORLD_H

#include "../configure/constants.h"
#include "../view/EntityFactory.h"
#include "../view/EntityView.h"
#include "entity/Player.h"
#include "maze/Maze.h"
#include <memory>
#include <string>


class World : public Subject {

private:
  std::shared_ptr<Player> player_;
  std::vector<std::shared_ptr<Entity>> entities_;
  std::vector<std::shared_ptr<Entity>> new_entities_;
  EntityFactory &factory_;
  std::vector<std::vector<char>> arena_grid_;
  std::shared_ptr<MazeNode> init_node_;

public:
  [[nodiscard]] const std::vector<std::shared_ptr<Entity>> &getEntities() const;
  [[nodiscard]] const std::vector<std::shared_ptr<Entity>> &
  getNewEntities() const;

public:
  explicit World(EntityFactory &factory) : factory_(factory) {};

  void initialize();

  bool isValidPosition(float x, float y) const;

  bool isPassage(float x, float y) const;

  void updateAllEntities();

  void checkInitialization() const;

  [[nodiscard]] Player *getPlayer() const;

  void update();

  void checkCollisions();

  void createPlayer(float x, float y);

  void createPlayer(std::shared_ptr<MazeNode> node);

  void cleanupEntities();

  void placeWall(unsigned int row, unsigned int column);

  void makeWall();
};

#endif // DOODLEJUMP_WORLD_H
