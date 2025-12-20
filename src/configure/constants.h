#ifndef PACMAN_CONSTANTS_H
#define PACMAN_CONSTANTS_H

#include <string>

namespace Config {
inline constexpr int LEADERBOARD_LIMIT = 5;
inline const std::string MazeFile = "input/maze2.txt";
namespace TextureFiles {
inline const std::string background = "assets/background/bck@2x.png";
inline const std::string sprites_json = "assets/textures.json";
} // namespace TextureFiles

namespace Window {
inline constexpr unsigned int CELL_WIDTH = 40;

} // namespace Window

namespace Player {
inline constexpr float SCALE = 1;
inline constexpr float WIDTH = 40;
inline constexpr float HEIGHT = 40;
inline constexpr float SPEED = 150;
} // namespace Player

namespace Ghost {
inline constexpr float SPEED = 100;
inline constexpr float WIDTH = 40;
inline constexpr float HEIGHT = 40;
inline constexpr float FRIGHTENED_DURATION = 10;
}

namespace Score {
inline constexpr int COIN_MODIFIER = 7;
inline constexpr int GHOST_MODIFIER = 300;
inline constexpr int FRUIT_MODIFIER = 60;
}

} // namespace Config

#endif // PACMAN_CONSTANTS_H
