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

// todo docs
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

  /// general update
  virtual void update() = 0;

  /// on collision
  virtual void onCollision(Entity *other){};

  /// returns entity type
  virtual EntityType getType() const = 0;

  /// sets state
  void setState(State state);

  /// returns current state
  [[nodiscard]] State getCurrentState() const;

  /// returns current mode
  Mode getMode() const;

  /// activates
  virtual void activate() { is_active_ = true; }

  /// deactivates
  virtual void deactivate();

  /// notifies deactivate to observers
  void notifyDeactivate();

  /// true if active
  [[nodiscard]] bool isActive() const { return is_active_; }

  /// moves in direction with speed
  void move(const Direction &direction, float speed);

  /// returns scale
  [[nodiscard]] float getScale() const;

  /// sets scale
  void setScale(float scale);

  /// returns width
  [[nodiscard]] float getWidth() const;

  /// sets width
  void setWidth(float width);

  /// returns height
  [[nodiscard]] float getHeight() const;

  /// sets height
  void setHeight(float height);

  /// returns position
  virtual MyVector getPosition() const { return position_; }

  /// sets position
  void setPosition(const MyVector &position) { position_ = position; }

  /// returns bottom (y coord)
  [[nodiscard]] float getBottom() const;

  /// sets bottom (y coord)
  void setBottom(float y);

  /// returns top (y coord)
  [[nodiscard]] float getTop() const;

  /// returns left (x coord)
  [[nodiscard]] float getLeft() const;

  /// returns right (x coord)
  [[nodiscard]] float getRight() const;

  /// returns bounding box
  [[nodiscard]] BoundingBox getBoundingBox() const;

  /// returns boundingbox of spawn location
  [[nodiscard]] const BoundingBox &getSpawn() const;

  /// returns center (x coord)
  [[nodiscard]] float getCenterX() const;

  /// returns center (y coord)
  float getCenterY() const;

  /// returns behavior on collision
  virtual CollisionBehavior getCollisionBehavior(EntityType type) const = 0;
};

#endif // ENTITY_H
