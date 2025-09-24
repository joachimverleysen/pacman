#include "EntityFactory.h"
#include "../../view/Game.h"
#include "Player.h"

std::shared_ptr<Player> EntityFactory::createPlayer(float x, float y,
                                                    float speed) {
  // todo: no hardcoded
  float WIDTH = 31;
  float HEIGHT = 29;
  float SCALE = 3;
  std::shared_ptr<Player> player =
      std::make_shared<Player>(x, y, WIDTH, HEIGHT, SCALE);
  return player;
}
