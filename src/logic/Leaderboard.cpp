#include "Leaderboard.h"

std::vector<int> Leaderboard::getScores() const {
  std::vector<int> result;
  std::string text;
  while (filereader_.getLine(text))
    result.push_back(std::stoi(text));
  return result;
}

void Leaderboard::writeScores(std::vector<int> &scores) {
  for (const auto num : scores)
    filewriter_.write(std::to_string(num));
}

void Leaderboard::addScore(int score) {
  std::vector<int> scores = getScores();
  scores.push_back(score);
  std::sort(scores.begin(), scores.end());
  writeScores(scores);
}
