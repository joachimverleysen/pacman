#ifndef DOODLEJUMP_ABSTRACTFACTORY_H
#define DOODLEJUMP_ABSTRACTFACTORY_H

#include "Entity.h"
#include "Player.h"
#include <memory>

class AbstractFactory {
public:
  virtual std::shared_ptr<Player> createPlayer() = 0;
  virtual ~AbstractFactory() = default;
};

#endif // DOODLEJUMP_ABSTRACTFACTORY_H
