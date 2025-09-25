#include "Game.h"
#include "../configure/constants.h"
#include <iostream>

Game::Game(sf::RenderWindow &window)
    : window_(window){
  setup();
}

void Game::update() {
  window_.clear();
  window_.draw(background_sprite_);
  float delta_time = Stopwatch::getInstance()->getDeltaTime();
  world_->update(delta_time);
  window_.display();

  Stopwatch::getInstance()->capFramerate(100);
}

void Game::run() {
  if (getState() != State::RUNNING) {
    close();
  }
  handleInput();
  update();
}

void Game::setup() {
  sf::Texture background_texture;
  // Set file_background texture + sprite
  if (!background_texture_.loadFromFile(Config::TextureFiles::background)) {
    throw std::runtime_error("Invalid file_background path");
  }
  background_sprite_.setTexture(background_texture_);
  try {
    factory_ = std::make_unique<EntityFactory>(*this, window_);
    world_ = std::make_shared<World>(*factory_);
    controller_ = std::make_unique<GameController>(*world_);
    std::shared_ptr<EntityFactory> view_factory_ =
        std::make_shared<EntityFactory>(*this, window_);
  } catch (std::runtime_error &e) {
    std::cout << "Failed to initialize game: " << e.what() << std::endl;
    exit(1);
  }
}

void Game::handleInput() {
  for (auto event = sf::Event(); window_.pollEvent(event);) {
    handleEvent(event);
  }
  controller_->handleInput();
}

void Game::handleEvent(const sf::Event &event) {
  if (event.type == sf::Event::Closed) {
    close();
  }
}

void Game::close() {
  std::cout << "GAME OVER\n";
  state_ = State::GAME_OVER;
  window_.close();
  exit(0);
}

Game::State Game::getState() const {
  if (!world_->getPlayer())
    return State::GAME_OVER;
  return State::RUNNING;
}
