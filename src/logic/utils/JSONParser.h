#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "../../view/view/EntityView.h"
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

#endif // JSONPARSER_H
