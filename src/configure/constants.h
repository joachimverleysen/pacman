#ifndef DOODLEJUMP_CONSTANTS_H
#define DOODLEJUMP_CONSTANTS_H

#include <string>

namespace Config {
namespace TextureFiles {
inline const std::string background = "assets/background/bck@2x.png";
inline const std::string sprites_json = "assets/textures.json";
} // namespace TextureFiles

namespace Arena {
} // namespace Arena
namespace Window {
inline const float BASE_SCALE = 0.001;
inline const unsigned int UNIT_LENGTH = 50;

} // namespace Window

namespace Player {
inline const float SCALE = 1;
inline const float WIDTH = 40;
inline const float HEIGHT = 40;
inline const float SPEED = 500;
} // namespace Player

namespace Collision {
inline const float min_x_distance = 20;
inline const float max_y_distance = 30;
} // namespace Collision
} // namespace Config

#endif // DOODLEJUMP_CONSTANTS_H
