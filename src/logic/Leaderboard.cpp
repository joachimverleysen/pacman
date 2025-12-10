#include "Leaderboard.h"
#include "../configure/constants.h"

Leaderboard* Leaderboard::instance_ = nullptr;
void Leaderboard::updateScores() {
  FileReader fr{scoreboard_};
  std::vector<int> result;
  std::string text;
  while (fr.getLine(text))
    result.push_back(std::stoi(text));
  fr.close();
  scores_ = result;
}

void Leaderboard::writeScores(std::vector<int> &scores) {
  FileWriter fw{scoreboard_};
  fw.clear();
  for (const auto num : scores)
    fw.write(std::to_string(num));
  fw.close();
}

void Leaderboard::limitScores(std::vector<int> &scores) {
  if (scores.size() <= 5) return;
  std::vector<int> final_scores{scores.begin(), scores.begin() + Config::LEADERBOARD_LIMIT};
  scores = final_scores;
}
void Leaderboard::addScore(int score) {
  scores_.push_back(score);
  std::sort(scores_.begin(), scores_.end());
  std::reverse(scores_.begin(), scores_.end());  // Highest score on top
  limitScores(scores_);
  writeScores(scores_);
}

const std::vector<int> &Leaderboard::getScores() const {
  return scores_;
}

Leaderboard::Leaderboard() {
  updateScores();
}
