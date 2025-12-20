#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include "../maze/Wall.h"
#include "../utils/TextConfig.h"
#include "Coin.h"
#include "Fruit.h"
#include "Ghost.h"
#include "Player.h"
#include "layout/Text.h"
#include <memory>

class AbstractFactory {
public:
  /// Creates player
  virtual std::shared_ptr<Player> createPlayer(NodePtr) = 0;

  /// Creates ghost
  virtual std::shared_ptr<Ghost> createGhost(NodePtr,
                                             std::shared_ptr<Player> player,
                                             Ghost::GhostType type) = 0;

  /// Creates wall
  virtual std::shared_ptr<Wall>
  createWall(std::vector<MazePosition> &positions) = 0;

  virtual ~AbstractFactory() = default;

  /// Creates coin
  virtual std::shared_ptr<Coin> createCoin(MazePosition) = 0;

  /// Creates fruit
  virtual std::shared_ptr<Fruit> createFruit(MazePosition) = 0;

  /// Creates text object
  virtual std::shared_ptr<Text> createText(MyVector vec,
                                           TextConfig &config) = 0;
};

#endif // ABSTRACT_FACTORY_H
