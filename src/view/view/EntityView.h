#ifndef ENTITYVIEW_H
#define ENTITYVIEW_H

#include "../../logic/entity/Entity.h"
#include "../../logic/observer/Observer.h"
#include "../TextureManager.h"
#include "../Visuals.h"
#include "SpriteDrawable.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

using FilePath = std::string;

class DrawableInterface;
class EntityView : public Observer {
  std::weak_ptr<Entity> entity_;
  MyVector position_{};
  bool foreground_{false};

public:
  const MyVector &getPosition() const;

protected:
  std::unique_ptr<DrawableInterface> drawable_;

public:
  EntityView(std::weak_ptr<Entity> entity,
             std::unique_ptr<DrawableInterface> drawable);

  EntityView(std::weak_ptr<Entity> entity);

  void update() override;

  virtual void draw(sf::RenderWindow &window);

  void setPosition(MyVector &position);

  /// Fetches position from corresponding entity
  void updatePosition();

  /// Pushes this view to the foreground of the scene
  void pushToForeground();

  [[nodiscard]] bool isForeGround() const;
};

#endif // ENTITYVIEW_H
