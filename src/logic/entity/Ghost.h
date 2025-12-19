#ifndef GHOST_H
#define GHOST_H
#include "../../configure/constants.h"
#include "../utils/Stopwatch.h"
#include "../utils/Utils.h"
#include "Character.h"
#include "Player.h"
#include "iostream"
#include <future>

class Ghost : public Character {
public:
  enum class GhostType {
    Orange, //  Locked to a random direction
    Red,    // Chases Pacman by prediction
    Pink,   // Chases Pacman directly
  };
  using Character::updateTarget;

  GhostType ghost_type_{GhostType::Orange};
  std::shared_ptr<Player> player_;
  unsigned int max_reversing_{1}; // Max times that ghost can reverse in a row
  unsigned int reverse_count_{0};
  std::weak_ptr<Timer> timeout_timer_{};
  std::shared_ptr<Timer> frightened_timer_;

public:
  Ghost() = delete;

  Ghost(NodePtr node, float width, float height, std::shared_ptr<Player> player,
        GhostType type);

  /// On collision
  void onCollision(Entity *other) override;

  [[nodiscard]] EntityType getType() const override;

  void update() override;

  Direction chooseRandomDirection(bool should_change) const;

  bool updateTarget(const std::vector<Direction> &options);

  /// Returns manhattan distance
  float getDistance2Player(Direction direction, float predictive_offset) const;

  /// Chooses direction according to type and state
  Direction chooseDirection();

  /// Chooses direction conform chase behavior
  Direction chooseChaseDirection(float predictive_offset) const;

  /// Chooses direction conform flee behavior
  Direction chooseFleeDirection() const;

  /// Chooses direction conform chase behavior in a smart way
  bool choosePredictedDirection(float offset);

  /// Chooses direction out of options
  bool chooseDirection(const std::vector<Direction> &options);

  void killPlayer() const;

  /// Chooses direction conform locking behavior
  Direction chooseLockingDirection() const;

  /// Finds any target node
  bool findAnyTarget();

  /// When colliding
  CollisionBehavior getCollisionBehavior(EntityType type) const override;

  /// Starts flee timer
  void startTimeOut(float seconds);

  /// True if I'm still timed out
  bool timeout() const;

  /// True if I'm still frightened
  bool frightened() const;

  void enterFrightenedMode(std::shared_ptr<Timer> timer);

  void enterChaseMode();

  /// Updates mode according to flee timer
  void updateMode();
};

#endif
