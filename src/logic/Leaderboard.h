#ifndef PACMAN_LEADERBOARD_H
#define PACMAN_LEADERBOARD_H

#include "utils/FileReader.h"
#include "utils/FileWriter.h"
#include <algorithm>
#include <string>
#include <vector>

class Leaderboard {
  static Leaderboard *instance_;
  std::string scoreboard_ = "output/scoreboard.txt";
  std::vector<int> scores_{};

  Leaderboard();

private:
  /// Fetches the scores from the output file

  /// Writes a list of scores to the output file
  void writeScores(std::vector<int> &scores);

public:
  const std::vector<int> &getScores() const;

public:
  static Leaderboard *getInstance() {
    if (!instance_)
      instance_ = new Leaderboard{};
    return instance_;
  }

  /// Adds a score to the leaderboard
  void addScore(int score);

  void limitEntries(int limit);

  void limitScores(std::vector<int> &scores);

  void updateScores();
};


#endif //PACMAN_LEADERBOARD_H
