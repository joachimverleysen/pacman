#ifndef PACMAN_TEXT_H
#define PACMAN_TEXT_H

#include <string>
#include "../Entity.h"

// todo Text should not be Entity
class Text : public Entity{

  std::string text_;
public:
  explicit Text(const std::string &text) : text_(text) {};

  void update() override {
    notifyObservers();
  }

  void onCollision(Entity *other) override {

  }

  EntityType getType() const override {
    return EntityType::Ghost;
  }

  void activate() override {
    Entity::activate();
  }

  void deactivate() override {
    Entity::deactivate();
  }

  MyVector getPosition() const override {
    return Entity::getPosition();
  }

  void setText(const std::string& text) {
    text_ = text;
    update();
  }

  const std::string getText() const {
    return text_;
  };

  CollisionBehavior getCollisionBehavior(EntityType type) const override {
    return CollisionBehavior::NONE;
  }
};


#endif //PACMAN_TEXT_H
