#include "logic/World.h"
#include "logic/entity/Player.h"
#include "view/Game.h"

int main() {

  Game game{};

  try {
    game.run();
  } catch (...) {
    std::cout << "Caught error in main" << std::endl;
    return 1;
  }
}
