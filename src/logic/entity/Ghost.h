#ifndef GHOST_H
#define GHOST_H
#include "../../configure/constants.h"
#include "../utils/Utils.h"
#include "Character.h"
#include "Player.h"
#include "iostream"
#include <future>

class Ghost : public Character {
  using Character::updateTarget;
  enum class Mode { FLEE, CHASE, RANDOM };

  Mode mode_{Mode::CHASE};
  std::shared_ptr<Player> player_;
  unsigned int max_reversing_{1}; // Max times that ghost can reverse in a row
  unsigned int reverse_count_{0};

public:
  Ghost() = delete;

  Ghost(NodePtr node, float width, float height,
        std::shared_ptr<Player> player);

  void onCollision(Entity *other) override;

  [[nodiscard]] EntityType getType() const override;

  void update() override;

  bool chooseRandomDirection();

  bool updateTarget(const std::vector<Direction> &options);

  float getDistance2Player(Direction direction) const;

  bool chooseDirection();

  bool chooseChaseDirection();

  bool chooseFleeDirection();
  bool chooseDirection(const std::vector<Direction> &options);

  void killPlayer() const;
};

#endif
