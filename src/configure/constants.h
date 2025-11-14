#ifndef PACMAN_CONSTANTS_H
#define PACMAN_CONSTANTS_H

#include <string>

namespace Config {
inline const std::string MazeFile = "input/maze2.txt";
namespace TextureFiles {
inline const std::string background = "assets/background/bck@2x.png";
inline const std::string sprites_json = "assets/textures.json";
} // namespace TextureFiles

namespace Window {
inline const unsigned int CELL_WIDTH = 35;

} // namespace Window

namespace Player {
inline const float SCALE = 1;
inline const float WIDTH = 40;
inline const float HEIGHT = 40;
inline const float SPEED = 300;
} // namespace Player

namespace Ghost {
inline const float SPEED = 300;
inline const float WIDTH = 40;
inline const float HEIGHT = 40;
}

} // namespace Config

#endif // PACMAN_CONSTANTS_H
