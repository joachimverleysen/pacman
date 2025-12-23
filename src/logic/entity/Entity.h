#ifndef ENTITY_H
#define ENTITY_H

#include "../observer/Subject.h"
#include "../utils/MyVector.h"
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
  enum class State { IDLE, LEFT, RIGHT, UP, DOWN, NONE };
  enum class Mode { NORMAL, FRIGHTENED };

protected:
  EntityType type_{EntityType::None};
  MyVector position_{0, 0};
  BoundingBox spawn_box_;
  float width_{0};
  float height_{0};
  float scale_{1};
  bool is_active_{true};
  State state_{State::IDLE};
  Mode mode_{Mode::NORMAL};
public:

public:
  Entity() = default;
  Entity(float width, float height, float scale = 1)
      : width_(width * scale), height_(height * scale), scale_(scale),
        spawn_box_(getBoundingBox()) {}
  virtual ~Entity() = default;

  virtual void update() = 0;
  virtual void onCollision(Entity *other){};
  virtual EntityType getType() const = 0;

  void setState(State state);
  [[nodiscard]] State getCurrentState() const;

  Mode getMode() const;

  virtual void activate() { is_active_ = true; }
  virtual void deactivate();
  void notifyDeactivate();
  [[nodiscard]] bool isActive() const { return is_active_; }

  void move(const Direction &direction, float speed);

  [[nodiscard]] float getScale() const;
  void setScale(float scale);

  [[nodiscard]] float getWidth() const;
  void setWidth(float width);

  [[nodiscard]] float getHeight() const;
  void setHeight(float height);

  virtual MyVector getPosition() const { return position_; }
  void setPosition(const MyVector &position) { position_ = position; }

  [[nodiscard]] float getBottom() const;
  void setBottom(float y);

  [[nodiscard]] float getTop() const;
  [[nodiscard]] float getLeft() const;
  [[nodiscard]] float getRight() const;

  [[nodiscard]] BoundingBox getBoundingBox() const;
  [[nodiscard]] const BoundingBox &getSpawn() const;

  [[nodiscard]] float getCenterX() const;
  float getCenterY() const;

  virtual CollisionBehavior getCollisionBehavior(EntityType type) const = 0;
};

#endif // ENTITY_H
