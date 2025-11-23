#ifndef GAME_H
#define GAME_H

#include "../logic/World.h"
#include "../view/controller/GameController.h"
#include "../logic/maze/Maze.h"
#include "../logic/observer/Observer.h"
#include "../logic/utils/Stopwatch.h"
#include "view/EntityView.h"
#include "Renderer.h"
#include "state/StateManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

struct MyVector;

class EntityFactory;

class Game : public Observer {
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

  void setup();
  void run();

  void update() override;

  void handleEvent(const sf::Event &event);

  void handleInput();

  void close();

  void updateState();
};

#endif // GAME_H
