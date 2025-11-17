#ifndef TEXTURE_PARSER_H
#define TEXTURE_PARSER_H

#include "../logic/utils/JSONParser.h"
#include "../logic/utils/json.hpp"
#include "view/EntityView.h"
#include "view/EntityView.h"

using json = nlohmann::json;

class TextureParser : public JSONParser {
private:
  json data_;

public:
  TextureParser() = default;

public:
  static Texture::StateTextures getStateTextures(const std::string &json_path,
                                                 const std::string &type);

  static sf::IntRect parseIntRect(const json &arr);

  static Entity::State getEntityState(const std::string &);

  static Texture::TextureMap getTextureMap(Texture::Types types, const std::string &json_path);
};

#endif // TEXTURE_PARSER_H
