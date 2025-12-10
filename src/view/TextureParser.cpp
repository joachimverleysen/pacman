#include "TextureParser.h"
#include "TextureManager.h"

sf::IntRect TextureParser::parseIntRect(const json &arr) {
  return sf::IntRect(arr[0], arr[1], arr[2], arr[3]);
}

std::map<std::string, Entity::Mode> MODES = {
    {"ghost-frightened", Entity::Mode::FRIGHTENED},
};

Texture::TextureMap TextureParser::getTextureMap(Texture::Types types,
                                                 const std::string &json_path) {
  Texture::TextureMap map;
  for (auto t : types) {
    auto state_map = getStateTextures(json_path, t);
    auto mode = Entity::Mode::NORMAL;
    if (MODES.find(t) != MODES.end())
      mode = MODES[t];
    map[mode] = state_map;
  }
  return map;
}

Texture::StateTextures
TextureParser::getStateTextures(const std::string &json_path,
                                const std::string &type) {
  Texture::StateTextures map;
  json json;
  loadJSONFile(json_path, json);

  if (json[type].items().begin() == json[type].items().end())
    throw std::runtime_error("Couldn't find type in json: " + type);
  for (auto &item : json[type].items()) {
    std::string animation_name = item.key();
    Entity::State state = getEntityState(animation_name);
    if (state == Entity::State::NONE)
      throw std::runtime_error("Unknown state in configuration file");
    for (auto &texture_config : item.value()) {
      auto area = parseIntRect(texture_config["area"]);
      auto texture = TextureManager::getTexture(
          texture_config["texture"].get<std::string>(), area);
      map[state].push_back(texture);
    }
  }
  return map;
}

Entity::State TextureParser::getEntityState(const std::string &state_name) {
  if (state_name == "idle")
    return Entity::State::IDLE;
  if (state_name == "left")
    return Entity::State::LEFT;
  if (state_name == "right")
    return Entity::State::RIGHT;
  if (state_name == "up")
    return Entity::State::UP;
  if (state_name == "down")
    return Entity::State::DOWN;
  return Entity::State::NONE;
}
