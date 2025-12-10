#include "Score.h"
#include "utils/FileWriter.h"

Score* Score::instance_ = nullptr;

void Score::handle(GhostEatenEvent &event) {
  // todo extract constants
  time_since_ghost_eaten_ = 0;
  value_ += std::max(
    ghost_eaten_modifier_ - 7 * time_since_ghost_eaten_, 150.f);
}

void Score::handle(CoinEatenEvent &event) {
  value_ += std::max(
    coin_eaten_modifier_ - 3.5f * time_since_last_coin_, 1.f);
  time_since_last_coin_ = 0;
}

void Score::update() {
  time_since_last_coin_ += Stopwatch::getInstance()->getDeltaTime();
  time_since_ghost_eaten_ += Stopwatch::getInstance()->getDeltaTime();
}

void Score::writeScoreToLeaderboard() const {
  FileWriter fw("output/score.txt");
  fw.write(std::to_string(value_));
}

void Score::handle(FruitEatenEvent &event) {
  value_ += fruit_eaten_modifier_;
}

void Score::handle(FrightenGhostsEvent &event) {


}

void Score::reset() {
  value_ = 0;
}
