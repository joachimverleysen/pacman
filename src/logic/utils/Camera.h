#ifndef CAMERA_h

#include "../../configure/constants.h"
#include "../../logic/utils/Position.h"
class Camera {
public:
  static Position world2Window(const Position &position);
  static Position window2World(const Position &position);
};

#endif // !CAMERA_h
