#ifndef LEADERBOARD_H
#include "utils/FileReader.h"
#include "utils/FileWriter.h"
#include <algorithm>
#include <string>
#include <vector>

class Leaderboard {
  Leaderboard *instance_;
  std::string scoreboard = "output/scoreboard.txt";
  FileWriter filewriter_{scoreboard};
  FileReader filereader_{scoreboard};

  Leaderboard() = default;

private:
  /// Fetches the scores from the output file
  std::vector<int> getScores() const;

  /// Writes a list of scores to the output file
  void writeScores(std::vector<int> &scores);

public:
  Leaderboard *getInstance() {
    if (!instance_)
      instance_ = new Leaderboard{};
    return instance_;
  }

  /// Adds a score to the leaderboard
  void addScore(int score);
};

#endif // !LEADERBOARD_H
