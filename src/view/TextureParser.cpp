//
// Created by joachimverleysen on 12/10/24.
//
#include "TextureParser.h"
#include "TextureManager.h"

sf::IntRect TextureParser::parseIntRect(const json &arr) {
  return sf::IntRect(arr[0], arr[1], arr[2], arr[3]);
}

Texture::TextureMap TextureParser::getTextureMap(const std::string &json_path,
                                                 const std::string &type) {
  Texture::TextureMap map;
  json json;
  loadJSONFile(json_path, json);

  for (auto &item : json[type].items()) {
    std::string animation_name = item.key();
    PacmanState state = getEntityState(animation_name);
    if (state == PacmanState::NONE)
      throw std::runtime_error("Unknown state in configuration file");
    auto area = parseIntRect(item.value()["area"]);
    auto texture = TextureManager::getTexture(
        item.value()["texture"].get<std::string>(), area);
    map[state] = texture;
  }
  return map;
}

// todo: why??
PacmanState TextureParser::getEntityState(const std::string &state_name) {
  if (state_name == "idle")
    return PacmanState::IDLE;
  if (state_name == "left")
    return PacmanState::LEFT;
  if (state_name == "right")
    return PacmanState::RIGHT;
  if (state_name == "up")
    return PacmanState::UP;
  if (state_name == "down")
    return PacmanState::DOWN;
  if (state_name == "triggered")
    return PacmanState::TRIGGERED;
  return PacmanState::NONE;
}
