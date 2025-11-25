#ifndef FILEWRITER_H
#include <fstream>

class FileWriter {
  std::ofstream out_stream_;
  std::string filename_;

public:
  FileWriter(const std::string &filename) : filename_(filename) {
    out_stream_.open(filename_, std::ofstream::app);
  }

  void write(const std::string &text) { out_stream_ << text << '\n'; };

  void close() { out_stream_.close(); }

  void clear() {
    out_stream_.open(filename_, std::ofstream::out | std::ofstream::trunc);
  }
};

#endif // !FILEWRITER_H
