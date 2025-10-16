//
// Created by joachimverleysen on 11/26/24.
//

#ifndef DOODLEJUMP_ENTITY_H
#define DOODLEJUMP_ENTITY_H

#include "../observer/Subject.h"
#include "../utils/Position.h"
#include "../utils/Utils.h"
#include "EntityType.h"

struct BoundingBox {
  BoundingBox() = default;
  BoundingBox(float top, float bottom, float left, float right)
      : top(top), bottom(bottom), left(left), right(right) {}

  BoundingBox &operator+=(float value) {
    top += value;
    bottom -= value;
    left -= value;
    right += value;
    return *this;
  }
  float top{};
  float bottom{};
  float left{};
  float right{};
};

class Entity : public Subject {

public:
  enum class State { IDLE, LEFT, RIGHT, UP, DOWN, TRIGGERED, NONE };

protected:
  EntityType type_{EntityType::None};
  Position position_{0, 0};
  BoundingBox spawn_box_;
  float width_{0};
  float height_{0};
  float scale_{1};
  bool is_active_{true};
  State state_{State::IDLE};

public:
  Entity() = default;

  void setState(State state);

  Entity(float x, float y)
      : position_(Position{x, y}), spawn_box_(getBoundingBox()) {}

  Entity(float width, float height, float scale)
      : width_(width * scale), height_(height * scale), scale_(scale),
        spawn_box_(getBoundingBox()) {}
  virtual ~Entity() = default;

public:
  virtual void update() = 0;

  const BoundingBox &getSpawn() const;

  virtual void onCollision(Entity *other) = 0;
  void move(const Direction &direction, float speed);
  virtual bool allowsSpawn(Entity *other) = 0;
  [[nodiscard]] State getCurrentState() const;

  virtual void activate() { is_active_ = true; };
  virtual void deactivate();
  void notifyDeactivate();
  [[nodiscard]] bool isActive() const { return is_active_; }

public:
  [[nodiscard]] virtual EntityType getType() const = 0;
  [[nodiscard]] float getScale() const;

  void setScale(float scale);

public:
  [[nodiscard]] float getWidth() const;

  void setWidth(float width);

  [[nodiscard]] float getHeight() const;

  void setHeight(float height);

public:
  [[nodiscard]] Position getPosition() const { return position_; };
  void setPosition(const Position &position) { position_ = position; };

  [[nodiscard]] float getBottom() const;

  void setBottom(float y);

  [[nodiscard]] float getTop() const;

  [[nodiscard]] float getLeft() const;
  [[nodiscard]] float getRight() const;
  [[nodiscard]] BoundingBox getBoundingBox() const;
  [[nodiscard]] float getCenterX() const;

  float getCenterY() const;
};

#endif // DOODLEJUMP_ENTITY_H
