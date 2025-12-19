#ifndef CAMERA_h

#include "../../configure/constants.h"
#include "../../logic/utils/MyVector.h"
class Camera {
public:
  /// Converts position from world to Window (e.g.)
  static MyVector world2Window(const MyVector &position);

  /// Converts position from window to world
  static MyVector window2World(const MyVector &position);
};

#endif // !CAMERA_h
