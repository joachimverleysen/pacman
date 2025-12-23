#include "Leaderboard.h"
#include "../configure/constants.h"
#include "utils/FileReader.h"
#include "utils/FileWriter.h"

Leaderboard* Leaderboard::instance_ = nullptr;
void Leaderboard::updateEntries() {
  FileReader fr{file_};
  std::vector<int> result;
  std::string text;
  while (fr.getLine(text))
    result.push_back(std::stoi(text));
  fr.close();
  entries_ = result;
}

void Leaderboard::writeScores(std::vector<int> &scores) {
  FileWriter fw{file_};
  fw.clear();
  for (const auto num : scores)
    fw.write(std::to_string(num));
  fw.close();
}

void Leaderboard::limitNrEntries(std::vector<int> &scores) {
  if (scores.size() <= 5) return;
  std::vector<int> final_scores{scores.begin(), scores.begin() + Config::LEADERBOARD_LIMIT};
  scores = final_scores;
}
void Leaderboard::addScore(int score) {
  entries_.push_back(score);
  std::sort(entries_.begin(), entries_.end());
  std::reverse(entries_.begin(), entries_.end());  // Highest score on top
  limitNrEntries(entries_);
  writeScores(entries_);
}

const std::vector<int> &Leaderboard::getEntries() const {
  return entries_;
}

Leaderboard::Leaderboard() {
  updateEntries();
}
