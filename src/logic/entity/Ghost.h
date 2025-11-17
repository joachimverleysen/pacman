#ifndef GHOST_H
#define GHOST_H
#include "../../configure/constants.h"
#include "../utils/Utils.h"
#include "Character.h"
#include "Player.h"
#include "iostream"
#include "../utils/Stopwatch.h"
#include <future>

class Ghost : public Character {
public:
  enum class GhostType {
    Orange,  //  Locked to a random direction
    Red,   // Chases Pacman by prediction
    Pink,  // Chases Pacman directly
  };
  using Character::updateTarget;
  enum class Mode { FRIGHTENED, CHASE, RANDOM };

  GhostType ghost_type_{GhostType::Orange};
  Mode mode_{Mode::CHASE};
  std::shared_ptr<Player> player_;
  unsigned int max_reversing_{1}; // Max times that ghost can reverse in a row
  unsigned int reverse_count_{0};
  std::weak_ptr<Timer> timeout_timer_{};
  std::shared_ptr<Timer> frightened_timer_;
  bool frightened_{false};

public:
  Ghost() = delete;

  Ghost(NodePtr node, float width, float height, std::shared_ptr<Player> player, GhostType type);

  void onCollision(Entity *other) override;

  [[nodiscard]] EntityType getType() const override;

  void update() override;

  Direction chooseRandomDirection(bool should_change);

  bool updateTarget(const std::vector<Direction> &options);

  float getDistance2Player(Direction direction, float predictive_offset) const;

  Direction chooseDirection();

  Direction chooseChaseDirection(float predictive_offset);

  Direction chooseFleeDirection();

  bool choosePredictedDirection(float offset);

  bool chooseDirection(const std::vector<Direction> &options);

  void killPlayer() const;

  Direction chooseLockingDirection();

  bool findAnyTarget();

  void startTimeOut(float seconds);

  bool timeout() const;

  bool frightened() const;

  void enterFrightenedMode(std::shared_ptr<Timer> timer);

  void enterChaseMode();

  void updateMode();
};

#endif
