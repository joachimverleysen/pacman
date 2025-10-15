#include "Game.h"
#include "../configure/constants.h"
#include "../logic/maze/Maze.h"
#include "Renderer.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

Game::Game()
    : window_(sf::RenderWindow({100, 100}, "Pacman", sf::Style::Close)) {
  setup();
}

void Game::update() {
  window_.clear();
  window_.draw(background_sprite_);
  world_->update();
  renderer_->render();
  window_.display();

  Stopwatch::getInstance()->capFramerate(100);
}

void Game::run() {
  while (window_.isOpen()) {
    if (getState() != State::RUNNING) {
      close();
    }
    handleInput();
    update();
  }
}

void Game::loadMaze(const std::string &filename) {
  std::vector<std::vector<char>> grid;
  std::string line;
  std::ifstream MazeFile(filename);
  while (std::getline(MazeFile, line)) {
    std::cout << line << '\n';
    std::vector<char> row{};
    row.reserve(line.size());
    for (char c : line) {
      if (c == 32) // Ignore Spaces
        continue;
      row.push_back(c);
    }
    grid.push_back(row);
  }
  Maze::getInstance()->loadGrid(grid);
}

void Game::setup() {
  auto maze = Maze::getInstance();
  loadMaze("input/maze2.txt");

  unsigned int UL = Config::Window::UNIT_LENGTH;
  window_.create({maze->getXunits() * UL, maze->getYunits() * UL}, "Pacman",
                 sf::Style::Close);

  // Set file_background texture + sprite
  sf::Texture background_texture;
  if (!background_texture_.loadFromFile(Config::TextureFiles::background)) {
    throw std::runtime_error("Invalid file_background path");
  }
  // background_sprite_.setTexture(background_texture_);
  try {

    factory_ = std::make_unique<EntityFactory>(*this, window_);
    world_ = std::make_shared<World>(*factory_);
    world_->initialize();
    controller_ = std::make_unique<GameController>(*world_);
    renderer_ = std::make_unique<Renderer>(window_, factory_);
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
}

void Game::handleEvent(const sf::Event &event) {
  if (event.type == sf::Event::Closed) {
    close();
  }
  if (event.type == sf::Event::KeyPressed) {
    controller_->handleInput(event);
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
