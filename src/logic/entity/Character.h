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

  bool overshotTarget() const;


  void updateDirection(Direction direction);

public:
  Character(NodePtr node, float width, float height);
  ~Character() override = default;

public:
  bool updateTarget(Direction direction);

  void update() override;

  void stop();

  void startMove();

  void reverseDirection();

  [[nodiscard]] Direction getTargetDirection() const;

  void setDirection(Direction direction);

  void takeTarget();

  void setTarget(NodePtr target);

  bool findAnyTarget();
};

#endif // !CHARACTER_H
