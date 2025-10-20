#include "../../configure/constants.h"
#include "../maze/Maze.h"
#include "../maze/MazeNode.h"
#include "Entity.h"
#include <memory>
#ifndef CHARACTER_H
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

  void updateNodes();

  bool overshotTarget() const;

  bool updateTarget(Direction direction);

  void updateDirection(Direction direction);

public:
  Character(NodePtr node, float width, float height);
  virtual ~Character() = default;

public:
  void update() override;

  void stop();

  void startMove();

  void reverseDirection();

  Direction getTargetDirection() const;

  void setDirection(Direction direction);

  bool getNewTarget(Direction direction) const;

  void takeTarget();

  void setTarget(NodePtr target);
};

#endif // !CHARACTER_H
