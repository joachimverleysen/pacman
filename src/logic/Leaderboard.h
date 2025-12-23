#ifndef PACMAN_LEADERBOARD_H
#define PACMAN_LEADERBOARD_H

#include <algorithm>
#include <string>
#include <vector>

class Leaderboard {
  static Leaderboard *instance_;
  std::string file_ = "output/scoreboard.txt";
  std::vector<int> entries_{};

  Leaderboard();

private:
  void writeScores(std::vector<int> &scores);

public:
  /// Returns a list of every entry currently stored
  const std::vector<int> &getEntries() const;

public:
  static Leaderboard *getInstance() {
    if (!instance_)
      instance_ = new Leaderboard{};
    return instance_;
  }

  /// Adds a score to the leaderboard
  void addScore(int score);

  /// Limits the number of entries that is displayed
  static void limitNrEntries(std::vector<int> &scores);

  /// Updates the entries that are displayed, based on the latest info
  void updateEntries();
};


#endif //PACMAN_LEADERBOARD_H
