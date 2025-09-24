#include "configure/constants.h"
#include "model/World.h"
#include "model/entity/Player.h"
#include "view/Game.h"
#include "view/Renderer.h"
#include <SFML/Graphics.hpp>
#include <filesystem>

int main() {
  auto window =
      sf::RenderWindow({Config::Window::WIDTH, Config::Window::HEIGHT},
                       "Pacman", sf::Style::Close);

  // todo : background doesnt need separate member

  Renderer renderer{window};
  Game game{window, renderer};

  while (window.isOpen()) {
    try {
      game.run();
    } catch (...) {
      std::cout << "Caught error in main" << std::endl;
      return 1;
    }
  }
}
