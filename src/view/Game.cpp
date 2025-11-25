#include "Game.h"
#include "../logic/utils/FileWriter.h"
#include "../configure/constants.h"
#include "../logic/maze/Maze.h"
#include "Renderer.h"
#include "../logic/utils/FileReader.h"
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

void Game::updateState() {
  if (state_manager_->empty())
    close();
  state_manager_->updateCurrentState();
}
void Game::update() {
  window_.clear();
  window_.draw(background_sprite_);
  updateState();
  renderer_->render(state_manager_->getCurrentStateView());
  Score::getInstance()->update();

  // End of function
  window_.display();
  Stopwatch::getInstance()->capFramerate(100);
}

void Game::run() {
  while (window_.isOpen()) {
    handleInput();
    update();
  }
}

void Game::loadMaze(const std::string &filename) {
  std::vector<std::vector<char>> grid;
  std::string line;
  std::ifstream MazeFile(filename);
  while (std::getline(MazeFile, line)) {
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
  loadMaze(Config::MazeFile);

  unsigned int UL = Config::Window::CELL_WIDTH;
  window_.create({maze->getXunits() * UL, maze->getYunits() * UL}, "Pacman",
                 sf::Style::Close);

  sf::Texture background_texture;
  if (!background_texture_.loadFromFile(Config::TextureFiles::background)) {
    throw std::runtime_error("Failed loading background texture from file");
  }
  try {

    state_manager_ = std::make_shared<StateManager>();
    state_manager_->setPtrToThis(state_manager_);
    factory_ = std::make_unique<EntityFactory>(state_manager_);
    state_manager_->setFactory(factory_);
    state_manager_->initialize();
    state_manager_->pushStartMenu(state_manager_);

    controller_ = std::make_unique<GameController>(state_manager_);
    renderer_ = std::make_unique<Renderer>(window_, factory_);
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
  std::cout << "End of program\n";
  window_.close();
  exit(0);
}

