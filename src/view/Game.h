#ifndef GAME_H
#define GAME_H

#include "../logic/World.h"
#include "../view/controller/GameController.h"
#include "graphics/Renderer.h"
#include "state/StateManager.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

#include "Dispatcher.h"

struct MyVector;

class EntityFactory;

class Game {
private:
  std::shared_ptr<StateManager> state_manager_;
  std::shared_ptr<EntityFactory> factory_;
  std::unique_ptr<GameController> controller_;
  sf::RenderWindow window_;
  sf::Sprite background_sprite_;
  sf::Texture background_texture_;
  std::unique_ptr<Renderer> renderer_{nullptr};


private:
  static void loadMaze(const std::string &);

private:
public:
  Game();

  /// Makes everything ready
  void setup();

  /// General run
  void run();

  /// General update
  void update();

  /// Handles specific event, e.g. Victory, Game Over etc.
  void handleEvent(const sf::Event &event);

  /// Handles user input
  void handleInput();

  /// Closes the game/window
  void close();

  /// Updates current state, e.g. VictoryState, GameOverState etc.
  void updateState();
};

#endif // GAME_H
