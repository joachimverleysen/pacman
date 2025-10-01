//
// Created by joachimverleysen on 11/27/24.
//

#include <fstream>
#include <iostream>
#include "JSONParser.h"



bool JSONParser::loadJSONFile(const std::string &filename) {
    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        throw std::runtime_error("Can't open file");
    }
    input_file >> data_;
    return true;

}

bool JSONParser::loadJSONFile(const std::string &filename, json& json_out) {
    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        throw std::runtime_error("Can't open file");
    }
    input_file >> json_out;
    return true;

}



