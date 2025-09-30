//
// Created by joachimverleysen on 11/26/24.
//

#ifndef DOODLEJUMP_WORLD_H
#define DOODLEJUMP_WORLD_H

#include "../view/EntityFactory.h"
#include "../view/EntityView.h"
#include "entity/Player.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <string>

class World : public Subject {

private:
  std::shared_ptr<Player> player_;
  std::vector<std::shared_ptr<Entity>> entities_;
  std::vector<std::shared_ptr<Entity>> new_entities_;
  EntityFactory &factory_;
  float speed_{10};

public:
  [[nodiscard]] const std::vector<std::shared_ptr<Entity>> &getEntities() const;
  [[nodiscard]] const std::vector<std::shared_ptr<Entity>> &
  getNewEntities() const;

public:
  explicit World(EntityFactory &factory) : factory_(factory) {
  };

  void initialize();

  void updateAllEntities();

  void checkInitialization() const;

  [[nodiscard]] Player *getPlayer() const;

  void update();

  void checkCollisions();

  void createPlayer(float x, float y);

  void cleanupEntities();
};

#endif // DOODLEJUMP_WORLD_H
