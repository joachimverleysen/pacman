#include "WallView.h"
#include "../logic/utils/Camera.h"
#include "../logic/maze/Maze.h"
#include <SFML/Graphics/RenderWindow.hpp>

void WallView::draw(sf::RenderWindow &window) {
//  std::vector<MazePosition> positions = {{0,0}, {5,5}};
  std::vector<MazePosition> positions = wall_.lock()->getPositions();
  using Config::Window::UNIT_LENGTH;
  for (auto maze_pos : positions) {
    drawable_->setPosition(
      Camera::world2Window(
        Maze::getInstance()->getWorldPosition(maze_pos.first, maze_pos.second))
        - Position{UNIT_LENGTH/2, UNIT_LENGTH/2}
        ) ;

    drawable_->draw(window);
  }
}
