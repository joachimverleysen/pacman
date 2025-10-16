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
  float speed_{SPEED * 0.01f};
  Direction direction_{Direction::LEFT};
  bool moving_{false};

public:
  NodePtr current_node_;
  NodePtr target_node_;

public:
  Character(NodePtr node, float width, float height, float scale);
  virtual ~Character() = default;

public:
  void move();

  void update() override;

  void updateNodes();

  bool overshotTarget() const;

  void updateTarget();

  void stop();

  void startMove();

private:
};

#endif // !CHARACTER_H
