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
    initialize();
    checkInitialization();
  };

  void initialize();

  void checkInitialization() const;

  [[nodiscard]] Player *getPlayer() const;

  void update(float delta_time);

  void checkCollisions();

  void createPlayer(float x, float y);

  void updateEntities(float delta_time);
};

#endif // DOODLEJUMP_WORLD_H
