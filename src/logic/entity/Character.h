#ifndef CHARACTER_H
#define CHARACTER_H
#include "../../configure/constants.h"
#include "../maze/Maze.h"
#include "../maze/MazeNode.h"
#include "Entity.h"
#include <memory>
typedef std::shared_ptr<MazeNode> NodePtr;
using Config::Player::SPEED;

class Character : public Entity {
protected:
  float speed_{SPEED};
  Direction direction_{Direction::LEFT};
  bool moving_{false};
  NodePtr current_node_;
  NodePtr target_node_;

protected:
  void move();

  /// True if Pacman crossed his target node
  bool overshotTarget() const;

  /// Sets a new direction and updates the state accordingly
  void updateDirection(Direction direction);

public:
  Character(NodePtr node, float width, float height);
  ~Character() override = default;

public:
  /// Updates target node
  bool updateTarget(Direction direction);

  /// General update
  void update() override;

  /// Stops moving
  void stop();

  /// Starts moving
  void startMove();

  void reverseDirection();

  /// Returns direction towards current target
  [[nodiscard]] Direction getTargetDirection() const;

  /// Sets direction
  void setDirection(Direction direction);

  /// takes some node as current
  void goTo(std::shared_ptr<MazeNode> node);

  /// Takes target as current
  void takeTarget();

  /// Sets target node
  void setTarget(NodePtr target);

  /// Finds any target node
  virtual bool findAnyTarget();

  /// Returns all viable directions
  std::vector<Direction> getPossibleDirections(NodePtr *node) const;

  /// True if I can teleport
  bool portalCheck();

  /// Returns current direction
  Direction getDirection() const;

  /// Sets new speed
  void setSpeed(float speed);
};

#endif // !CHARACTER_H
