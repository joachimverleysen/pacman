#ifndef PACMAN_FILEREADER_H
#define PACMAN_FILEREADER_H
#include <iostream>
#include <optional>
#include <fstream>
#include <string>

class FileReader {
  mutable std::ifstream in_stream_;

public:
  FileReader(const std::string &filename) : in_stream_(filename) {};

  bool getLine(std::string &text) const {
    getline(in_stream_, text);
    if (text.size() == 0)
      return false;
    return true;
  }

  void close() { in_stream_.close(); }
};

#endif //PACMAN_FILEREADER_H
