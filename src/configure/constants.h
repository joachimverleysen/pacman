#ifndef PACMAN_CONSTANTS_H
#define PACMAN_CONSTANTS_H

#include <string>

namespace Config {
inline const int LEADERBOARD_LIMIT = 5;
inline const std::string MazeFile = "input/maze2.txt";
namespace TextureFiles {
inline const std::string background = "assets/background/bck@2x.png";
inline const std::string sprites_json = "assets/textures.json";
} // namespace TextureFiles

namespace Window {
inline const unsigned int CELL_WIDTH = 40;

} // namespace Window

namespace Player {
inline const float SCALE = 1;
inline const float WIDTH = 40;
inline const float HEIGHT = 40;
inline const float SPEED = 150;
} // namespace Player

namespace Ghost {
inline const float SPEED = 100;
inline const float WIDTH = 40;
inline const float HEIGHT = 40;
inline const float FREIGHTENED_DURATION = 10;
}

} // namespace Config

#endif // PACMAN_CONSTANTS_H
