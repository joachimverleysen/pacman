#include "Game.h"
#include "../configure/constants.h"
#include <iostream>

Game::Game(sf::RenderWindow &window, Renderer &renderer)
    : window_(window), renderer_(renderer) {
  setup();
}

void Game::update() {
  renderer_.render();
  float delta_time = Stopwatch::getInstance()->getDeltaTime();
  game_world_->update(delta_time);

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
  try {
    factory_ = std::make_unique<EntityFactory>(*this);
    game_world_ = std::make_shared<World>(*factory_);
    controller_ = std::make_unique<GameController>(*game_world_);
    std::shared_ptr<EntityViewFactory> view_factory_ = std::make_shared<EntityViewFactory>(*game_world_);
    game_world_->addObserver(view_factory_);
    renderer_.setFactory(view_factory_);
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
  if (!game_world_->getPlayer())
    return State::GAME_OVER;
  return State::RUNNING;
}
