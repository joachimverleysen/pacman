#ifndef GHOST_H
#define GHOST_H
#include "../utils/Stopwatch.h"
#include "../utils/Utils.h"
#include "Character.h"
#include "Player.h"
#include <future>

class Ghost : public Character {
public:
  enum class GhostType {
    Orange, //  Locked to a random direction
    Red,    // Chases Pacman by prediction
    Pink,   // Chases Pacman directly
  };
  using Character::updateTarget;

  NodePtr start_node_;
  GhostType ghost_type_{GhostType::Orange};
  std::shared_ptr<Player> player_;
  unsigned int max_reversing_{1}; // Max times that ghost can reverse in a row
  unsigned int reverse_count_{0};
  std::weak_ptr<Timer> timeout_timer_{};
  std::shared_ptr<Timer> frightened_timer_;

public:
  Ghost() = delete;

  Ghost(NodePtr node, float width, float height, std::shared_ptr<Player> player,
        GhostType type, NodePtr start_node);

  /// On collision
  void onCollision(Entity *other) override;

  [[nodiscard]] EntityType getType() const override;

  void update() override;

  [[nodiscard]] Direction chooseRandomDirection(bool should_change) const;

  bool updateTarget(const std::vector<Direction> &options);

  /// Returns manhattan distance
  [[nodiscard]] float getDistance2Player(Direction direction, float predictive_offset) const;

[[nodiscard]] NodePtr start_node() const {
    return start_node_;
  }

  /// Chooses direction according to type and state
  Direction chooseDirection();

  /// Chooses direction conform chase behavior
  [[nodiscard]] Direction chooseChaseDirection(float predictive_offset) const;

  /// Chooses direction conform flee behavior
  [[nodiscard]] Direction chooseFleeDirection() const;

  /// Chooses direction conform locking behavior
  [[nodiscard]] Direction chooseLockingDirection() const;

  /// Finds any target node
  bool findAnyTarget() override;

  /// When colliding
  [[nodiscard]] CollisionBehavior getCollisionBehavior(EntityType type) const override;

  /// Starts flee timer
  void startTimeOut(float seconds);

  /// True if I'm still timed out
  [[nodiscard]] bool timeout() const;

  void enterFrightenedMode(std::shared_ptr<Timer> timer);

  void undoFrightenMode();

  /// Updates mode according to flee timer
  void updateMode();
};

#endif
