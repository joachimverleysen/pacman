//
// Created by joachimverleysen on 12/10/24.
//

#ifndef DOODLEJUMP_TEXTURE_PARSER_H
#define DOODLEJUMP_TEXTURE_PARSER_H

#include "../utils/json.hpp"
#include "../view/EntityView.h"
#include "EntityView.h"
#include "../utils/JSONParser.h"

using json = nlohmann::json;


class TextureParser : public JSONParser {
private:
    json data_;
public:
    TextureParser() = default;

public:

    static Texture::TextureMap getTextureMap(const std::string &json_path, const std::string &type);

    static sf::IntRect parseIntRect(const json &arr);

    static PacmanState getEntityState(const std::string &);
};

#endif //DOODLEJUMP_TEXTURE_PARSER_H