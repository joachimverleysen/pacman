#ifndef ENTITYVIEW_H
#define ENTITYVIEW_H

#include "../../logic/entity/Entity.h"
#include "../../logic/observer/Observer.h"
#include "SpriteDrawable.h"
#include "../TextureManager.h"
#include "../Visuals.h"
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

public:
  const MyVector &getPosition() const;

protected:
  std::unique_ptr<DrawableInterface> drawable_;

public:
  EntityView(std::weak_ptr<Entity> entity,
             std::unique_ptr<DrawableInterface> drawable);

  ~EntityView() override;

  void update() override;

  virtual void draw(sf::RenderWindow &window);

  void setPosition(MyVector &position);

  void updatePosition();
};

#endif // ENTITYVIEW_H
