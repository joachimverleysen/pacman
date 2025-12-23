#ifndef PACMAN_FONTMANAGER_H
#define PACMAN_FONTMANAGER_H

#include <SFML/Graphics/Font.hpp>
#include <memory>

class FontManager {
public:
  /// Returns font if existing
  static std::shared_ptr<sf::Font> get(const std::string &path) {
    static std::map<std::string, std::shared_ptr<sf::Font>> fonts;
    auto it = fonts.find(path);
    if (it != fonts.end())
      return it->second;
    auto font = std::make_shared<sf::Font>();
    if (!font->loadFromFile(path))
      throw std::runtime_error("Font load failed");
    fonts[path] = font;
    return font;
  }
};

#endif // PACMAN_FONTMANAGER_H
