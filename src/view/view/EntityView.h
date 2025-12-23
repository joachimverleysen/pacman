#ifndef ENTITYVIEW_H
#define ENTITYVIEW_H

#include "../../logic/entity/Entity.h"
#include "../../logic/observer/Observer.h"
#include "../graphics/Visuals.h"
#include "SpriteDrawable.h"
#include <SFML/Graphics.hpp>
#include <memory>
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

  /// General update
  void update() override;

  /// Draws view on window
  virtual void draw(sf::RenderWindow &window);

  /// Sets position
  void setPosition(MyVector &position);

  /// Fetches position from corresponding entity
  void updatePosition();

  /// Pushes this view to the foreground of the scene
  void pushToForeground();

  /// True if this view is on the foreground of the 'scene'
  [[nodiscard]] bool isForeGround() const;
};

#endif // ENTITYVIEW_H
