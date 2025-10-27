#ifndef WALL_VIEW_H
#define WALL_VIEW_H

#include "../logic/maze/Wall.h"
#include "DrawableInterface.h"
#include "EntityView.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class WallView : public EntityView {
  std::weak_ptr<Wall> wall_;

public:
  WallView(std::weak_ptr<Wall> wall,
           std::unique_ptr<DrawableInterface> drawable)
      : EntityView(wall, std::move(drawable)), wall_(wall) {}

  void draw(sf::RenderWindow &window) override;

  void update() override {};
};
#endif // !WALL_VIEW_H
