#ifndef CAMERA_h

#include "../configure/constants.h"
#include "../logic/utils/Position.h"
class Camera {
public:
  static Position world2SFML(const Position &position);
  static Position SFML2World(const Position &position);
};

#endif // !CAMERA_h
