#ifndef PACMAN_TEXTCONFIG_H
#define PACMAN_TEXTCONFIG_H

#include "Utils.h"

struct Color {
  int r{255};
  int g{255};
  int b{255};
};

struct TextConfig {
  std::string text;
  Color fill_color{255, 255, 255};
  Color outline_color{255, 0, 0};
  float outline_thickness{2};
  int character_size{30};
  std::string font{MyFont::LIBER};
};
#endif //PACMAN_TEXTCONFIG_H
