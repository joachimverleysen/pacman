#ifndef PACMAN_TEXT_H
#define PACMAN_TEXT_H

#include <string>
#include "../Entity.h"

class Text : public Entity{

  std::string string_;
public:
  explicit Text(const std::string &text) : string_(text) {};

  /// General update
  void update() override {
    notifyObservers();
  }

  /// Handles entity collision (unused)
  void onCollision(Entity *other) override {

  }

  /// Returns entity type
  EntityType getType() const override {
    return EntityType::Ghost;
  }

  void activate() override {
    Entity::activate();
  }

  void deactivate() override {
    Entity::deactivate();
  }

  /// Returns position
  MyVector getPosition() const override {
    return Entity::getPosition();
  }

  /// sets string
  void setString(const std::string& text) {
    string_ = text;
    update();
  }

  /// sets string
  const std::string getString() const {
    return string_;
  };

  /// returns collision behavior (unused)
  CollisionBehavior getCollisionBehavior(EntityType type) const override {
    return CollisionBehavior::NONE;
  }
};

#endif //PACMAN_TEXT_H
