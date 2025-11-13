#ifndef RENDERER_H
#define RENDERER_H

#include "EntityFactory.h"
#include "view/EntityView.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>

class StateView;
class Renderer {
  sf::RenderWindow &window_;
  std::weak_ptr<EntityFactory> factory_;
  std::vector<std::weak_ptr<EntityView>> views_;

public:
  Renderer(sf::RenderWindow &window, std::weak_ptr<EntityFactory> factory)
      : window_(window), factory_(factory) {}

public:
  void render();

  void updateViews();

  void removeView(std::weak_ptr<EntityView>);

  void render(const std::weak_ptr<StateView>& weakPtr);

  void updateViews(const std::weak_ptr<StateView>& state_view);
};
#endif // !RENDERER_H
