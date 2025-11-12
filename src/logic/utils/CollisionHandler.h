#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "../entity/Entity.h"

class CollisionHandler {
public:
  static bool checkCollision(const Entity *first, const Entity *second);

  static bool checkCollision(const BoundingBox &first,
                             const BoundingBox &second);
  static bool checkCollision(const BoundingBox &first,
                             const BoundingBox &second, float margin);
  static bool onCollision(Entity *first, Entity *second);

  bool checkCollision(const Entity *first, const Entity *second, float margin);
};

#endif // COLLISION_HANDLER_H
