#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "../entity/Entity.h"

class CollisionHandler {
public:
  /// Returns event according to possible collision
  static std::shared_ptr<Event> checkCollision(const Entity *first,
                                               const Entity *second);

  /// true if collision
  static bool checkCollision(const BoundingBox &first,
                             const BoundingBox &second);

  /// true if collision with margin
  static bool checkCollision(const BoundingBox &first,
                             const BoundingBox &second, float margin);

  /// called when collision happens
  static bool onCollision(Entity *first, Entity *second);

  /// true if collision with margin
  bool checkCollision(const Entity *first, const Entity *second, float margin);
};

#endif // COLLISION_HANDLER_H
