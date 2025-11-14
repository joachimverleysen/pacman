#ifndef PACMAN_TEXT_H
#define PACMAN_TEXT_H

#include <string>
#include "../Entity.h"

class Text : public Entity{

  std::string text_;
public:
  explicit Text(const std::string &text) : text_(text) {};

  void update() override {

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
};


#endif //PACMAN_TEXT_H
