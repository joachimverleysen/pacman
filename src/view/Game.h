//
// Created by joachimverleysen on 11/26/24.
//

#ifndef DOODLEJUMP_GAME_H
#define DOODLEJUMP_GAME_H

#include "../controller/GameController.h"
#include "../model/Stopwatch.h"
#include "../model/World.h"
#include "../model/observer/Observer.h"
#include "EntityView.h"
#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

struct Position;

class EntityFactory;

class Game : public Observer {
public:
  enum class State { RUNNING, GAME_OVER };

private:
  State state_{State::RUNNING};
  std::unique_ptr<EntityFactory> factory_;
  std::shared_ptr<World> game_world_;
  std::unique_ptr<GameController> controller_;
  sf::RenderWindow &window_;

private:
  Renderer &renderer_;

public:
  Game(sf::RenderWindow &window,
       Renderer &renderer);

  void setup();
  void run();

  State getState() const;

  void update() override;

  void handleEvent(const sf::Event &event);

  void handleInput();

  void close();
};

#endif // DOODLEJUMP_GAME_H
