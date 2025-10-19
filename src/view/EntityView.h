#ifndef DOODLEJUMP_ENTITYVIEW_H
#define DOODLEJUMP_ENTITYVIEW_H

#include "../logic/entity/Entity.h"
#include "../logic/observer/Observer.h"
#include "SpriteDrawable.h"
#include "TextureManager.h"
#include "Visuals.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

using FilePath = std::string;

class DrawableInterface;
class EntityView : public Observer {
  std::unique_ptr<DrawableInterface> drawable_;
  std::weak_ptr<Entity> entity_;
  Position position_{};

public:
  const Position &getPosition() const;

private:

public:
  EntityView(std::weak_ptr<Entity> entity,
             std::unique_ptr<DrawableInterface> drawable);

  ~EntityView() override;

  void update() override;

  virtual void draw(sf::RenderWindow &window);

  void setPosition(Position &position);

  void updatePosition();
};

#endif // DOODLEJUMP_ENTITYVIEW_H
