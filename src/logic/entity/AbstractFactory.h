#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include "Entity.h"
#include "Player.h"
#include "Wall.h"
#include <memory>

class AbstractFactory {
public:
  virtual std::shared_ptr<Player> createPlayer(NodePtr) = 0;
  virtual std::shared_ptr<Wall> createWall(unsigned int row, unsigned int column) = 0;
  virtual ~AbstractFactory() = default;
};

#endif // ABSTRACT_FACTORY_H
