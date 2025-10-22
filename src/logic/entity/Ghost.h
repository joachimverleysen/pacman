#ifndef GHOST_H
#define GHOST_H
#include "../../configure/constants.h"
#include "../utils/Utils.h"
#include "Character.h"
#include "iostream"
#include <future>

class Ghost : public Character {
public:
  Ghost() = delete;

  Ghost(NodePtr node, float width, float height);

  bool allowsSpawn(Entity *other) override;

  void onCollision(Entity *other) override;

  [[nodiscard]] EntityType getType() const override;

  void update();

  bool chooseDirection();

  bool chooseDirection(std::vector<Direction> options);
};

#endif
