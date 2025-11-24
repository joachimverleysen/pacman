#include "Score.h"

void Score::handle(GhostEatenEvent &event) {
  // todo extract constants
  time_since_ghost_eaten_ = 0;
  value += std::max(
    ghost_eaten_modifier_ - 7 * time_since_ghost_eaten_, 150.f);
}

void Score::handle(CoinEatenEvent &event) {
  value += std::max(
    coin_eaten_modifier_ - 3.5f * time_since_last_coin_, 1.f);
  time_since_last_coin_ = 0;
}

void Score::update() {
  time_since_last_coin_ += Stopwatch::getInstance()->getDeltaTime();
  time_since_ghost_eaten_ += Stopwatch::getInstance()->getDeltaTime();
  display_->setText("Score: " + std::to_string(value));
}

void Score::handle(FruitEatenEvent &event) {
  value += fruit_eaten_modifier_;
}

void Score::handle(FrightenGhostsEvent &event) {


}
