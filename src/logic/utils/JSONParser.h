//
// Created by joachimverleysen on 11/27/24.
//

#ifndef DOODLEJUMP_JSONPARSER_H
#define DOODLEJUMP_JSONPARSER_H

#include "../../view/EntityView.h"
#include "json.hpp"

using json = nlohmann::json;

class JSONParser {
private:
  json data_;

public:
  JSONParser() = default;

public:
  bool loadJSONFile(const std::string &filename);

  static bool loadJSONFile(const std::string &filename, json &json_out);
};

#endif // DOODLEJUMP_JSONPARSER_H
