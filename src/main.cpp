#include "logic/World.h"
#include "logic/entity/Player.h"
#include "view/Game.h"

int main() {

  Game game{};

  try {
    game.run();
  } catch(std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
    exit(1);
  }
  catch (...) {
    std::cout << "Caught error in main" << std::endl;
    exit(1);
  }
}
