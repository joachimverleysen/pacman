//
// Created by joachimverleysen on 12/12/24.
//

#ifndef DOODLEJUMP_CONSTANTS_H
#define DOODLEJUMP_CONSTANTS_H

#include <string>

namespace Config {
namespace TextureFiles {
inline const std::string background = "assets/background/bck@2x.png";
inline const std::string sprites_json = "assets/textures.json";
} // namespace TextureFiles

namespace Arena {
inline const unsigned int X_UNITS = 20;
inline const unsigned int Y_UNITS = 10;
} // namespace Arena
namespace Window {
inline const float BASE_SCALE = 0.001;
inline const unsigned int UNIT_LENGTH = 100;
inline const unsigned int WIDTH = 620; // 620
inline const unsigned int HEIGHT = 700;

} // namespace Window

namespace Player {
inline const float SCALE = 1;
inline const float WIDTH = 40;
inline const float HEIGHT = 40;
inline const float SPEED = 20;
} // namespace Player

namespace Camera {
inline const float top_margin = 300;
inline const float scroll_distance = 300;
inline const float min_scroll_speed = 100.0f;
inline const float max_scroll_speed = 400.0f;
} // namespace Camera

namespace Platform {
inline const float SPEED = 200;
inline const float WIDTH = 100;
inline const float HEIGHT = 30;
inline const float MOVING_DISTANCE = 300;

} // namespace Platform

namespace Collision {
inline const float min_x_distance = 20;
inline const float max_y_distance = 30;
} // namespace Collision

} // namespace Config

namespace CameraConfig {}

// Collision offsets (technical)

#endif // DOODLEJUMP_CONSTANTS_H
