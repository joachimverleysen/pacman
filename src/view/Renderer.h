#ifndef RENDERER_H
#define RENDERER_H

#include "EntityFactory.h"
#include "EntityView.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>
class Renderer {
  sf::RenderWindow &window_;
  std::weak_ptr<EntityFactory> factory_;
  std::vector<std::weak_ptr<EntityView>> views_;

public:
  Renderer(sf::RenderWindow &window, std::weak_ptr<EntityFactory> factory)
      : window_(window), factory_(factory) {}

public:
  void render();


};
#endif // !RENDERER_H
