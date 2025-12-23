#ifndef SCORE_H
#include "entity/layout/Text.h"
#include "utils/Stopwatch.h"
#include "utils/Visitor.h"
#include <algorithm>
#include <iostream>

class FruitEatenEvent;
class FrightenGhostsEvent;

// todo: score should not be Entity
class Score : public Visitor {
  int value_{0};
  float time_since_last_coin_{0};
  float time_since_ghost_eaten_{0};
  static Score *instance_;

private:
  Score() {};

public:
  static Score *getInstance() {
    if (!instance_)
      instance_ = new Score{};
    return instance_;
  }

  /// Resets score value
  void reset();

  /// General update
  void update();

  /// Visitor function to modify score based on payload in event object
  /// idem for the other 'visit' functions
  void visit(CoinEatenEvent &event) override;

  void visit(FruitEatenEvent &event) override;

  void visit(GhostEatenEvent &event) override;

  void visit(PacmanDiesEvent &event) override;

  void visit(FrightenGhostsEvent &event) override;

  void visit(NewLevelEvent &event) override;

  /// Returns current score value
  int getValue() const { return value_; }

  /// Writes score to leaderboard
  void writeScoreToLeaderboard() const;
};

#endif // !SCORE_H
