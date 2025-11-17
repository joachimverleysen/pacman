//
#include "Entity.h"

float Entity::getBottom() const { return position_.y - 0.5 * height_; }

float Entity::getTop() const { return position_.y + 0.5 * height_; }

float Entity::getLeft() const { return position_.x - 0.5 * width_; }

float Entity::getRight() const { return position_.x + 0.5 * width_; }

Entity::State Entity::getCurrentState() const { return state_; }

float Entity::getScale() const { return scale_; }

void Entity::setScale(float scale) { scale_ = scale; }

float Entity::getWidth() const { return width_; }

void Entity::setWidth(float width) { width_ = width; }

float Entity::getHeight() const { return height_; }

void Entity::setHeight(float height) { height_ = height; }

BoundingBox Entity::getBoundingBox() const {
  return {getTop(), getBottom(), getLeft(), getRight()};
}

void Entity::setBottom(float y) { position_.y = y + height_; }

void Entity::move(const Direction &direction, float speed) {
  if (direction == Direction::LEFT)
    position_.x -= speed;
  if (direction == Direction::RIGHT)
    position_.x += speed;
  if (direction == Direction::UP)
    position_.y += speed;
  if (direction == Direction::DOWN)
    position_.y -= speed;
}

float Entity::getCenterX() const { return (getLeft() + getRight()) / 2; }

float Entity::getCenterY() const { return (getTop() + getBottom()) / 2; }

const BoundingBox &Entity::getSpawn() const { return spawn_box_; }

void Entity::setState(State state) { state_ = state; }

void Entity::notifyDeactivate() {
  for (auto &o : observers_)
    o->onDeactivate();
}

void Entity::deactivate() {
  is_active_ = false;
  notifyDeactivate();
}

Entity::Mode Entity::getMode() const {
  return mode_;
}
