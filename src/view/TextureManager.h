//
// Created by joachimverleysen on 11/26/24.
//

#ifndef DOODLEJUMP_TEXTUREMANAGER_H
#define DOODLEJUMP_TEXTUREMANAGER_H


#include <SFML/Graphics/Texture.hpp>
#include <map>

using TextureConfig = std::pair<std::string, const sf::IntRect>;

namespace std {
    // Add comparison operator for TextureConfig
    template <>
    struct less<TextureConfig> {
        bool operator()(const TextureConfig& lhs, const TextureConfig& rhs) const {
            if (lhs.first != rhs.first)
                return lhs.first < rhs.first;
            return lhs.second.top < rhs.second.top;
        }
    };
}

class TextureManager {
public:

    static const sf::Texture *getTexture(const std::string &textureFile, const sf::IntRect& area) {
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

#endif //DOODLEJUMP_TEXTUREMANAGER_H




