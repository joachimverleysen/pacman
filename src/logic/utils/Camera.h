#ifndef CAMERA_h

#include "../../configure/constants.h"
#include "../../logic/utils/MyVector.h"
class Camera {
public:
  static MyVector world2Window(const MyVector &position);
  static MyVector window2World(const MyVector &position);
};

#endif // !CAMERA_h
