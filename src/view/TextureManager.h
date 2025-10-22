#ifndef DOODLEJUMP_TEXTUREMANAGER_H
#define DOODLEJUMP_TEXTUREMANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <stdexcept>

//using TextureConfig = std::pair<std::string, const sf::IntRect>;

struct TextureConfig {
    std::string file;
    sf::IntRect area;

    bool operator<(const TextureConfig& other) const {
        return std::tie(file, area.left, area.top, area.width, area.height) <
               std::tie(other.file, other.area.left, other.area.top, other.area.width, other.area.height);
    }
};


class TextureManager {
public:
  static const sf::Texture *getTexture(const std::string &textureFile,
                                       const sf::IntRect &area) {
    static std::map<TextureConfig, sf::Texture> textures;
    TextureConfig config{textureFile, area};
    auto it = textures.find(config);
    if (it == textures.end()) {
      // If not texture not found then load it
      sf::Texture newTexture;
      if (!newTexture.loadFromFile(textureFile, area)) {
        throw std::runtime_error("Failed to load texture: " + textureFile);
      }
      it = textures.emplace(config, std::move(newTexture)).first;
    }
    return &it->second;
  }
};

#endif // DOODLEJUMP_TEXTUREMANAGER_H
