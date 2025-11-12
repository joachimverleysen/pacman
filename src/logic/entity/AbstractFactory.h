#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include "../maze/Wall.h"
#include "Entity.h"
#include "Ghost.h"
#include "Player.h"
#include <memory>

class AbstractFactory {
public:
  virtual std::shared_ptr<Player> createPlayer(NodePtr) = 0;
  /* virtual std::shared_ptr<Wall> createWall(unsigned int row,
                                           unsigned int column) = 0; */
  virtual std::shared_ptr<Ghost> createGhost(NodePtr, std::shared_ptr<Player> player) = 0;
  virtual std::shared_ptr<Wall>
  createWall(std::vector<MazePosition> &positions) = 0;
  virtual ~AbstractFactory() = default;
};

#endif // ABSTRACT_FACTORY_H
