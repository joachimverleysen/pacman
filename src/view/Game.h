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
  std::shared_ptr<World> world_;
  std::unique_ptr<GameController> controller_;
  sf::RenderWindow &window_;
  sf::Sprite background_sprite_;
  sf::Texture background_texture_;
private:

public:
  Game(sf::RenderWindow &window
       );

  void setup();
  void run();

  State getState() const;

  void update() override;

  void handleEvent(const sf::Event &event);

  void handleInput();

  void close();
};

#endif // DOODLEJUMP_GAME_H
