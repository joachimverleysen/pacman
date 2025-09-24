//
// Created by joachimverleysen on 12/10/24.
//
#include "TextureParser.h"
#include "TextureManager.h"

sf::IntRect TextureParser::parseIntRect(const json &arr) {
  return sf::IntRect(arr[0], arr[1], arr[2], arr[3]);
}

Visuals::TextureMap TextureParser::getTextureMap(const std::string &json_path,
                                                 const std::string &type) {
  Visuals::TextureMap map;
  json json;
  loadJSONFile(json_path, json);

  for (auto &item : json[type].items()) {
    std::string animation_name = item.key();
    EntityState state = getEntityState(animation_name);
    if (state == EntityState::NONE)
      throw std::runtime_error("Unknown state in configuration file");
    auto area = parseIntRect(item.value()["area"]);
    auto texture = TextureManager::getTexture(
        item.value()["texture"].get<std::string>(), area);
    map[state] = texture;
  }
  return map;
}

// todo: why??
EntityState TextureParser::getEntityState(const std::string &state_name) {
  if (state_name == "idle")
    return EntityState::IDLE;
  if (state_name == "left")
    return EntityState::LEFT;
  if (state_name == "right")
    return EntityState::RIGHT;
  if (state_name == "triggered")
    return EntityState::TRIGGERED;
  return EntityState::NONE;
}
