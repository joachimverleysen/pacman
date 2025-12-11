#ifndef SCORE_H
#include <iostream>
#include <algorithm>
#include "entity/layout/Text.h"
#include "utils/Stopwatch.h"
#include "utils/Visitor.h"

class FruitEatenEvent;
class FrightenGhostsEvent;

// todo: score should not be Entity
class Score: public Visitor {
  int value_{0};
  float time_since_last_coin_{0};
  float time_since_ghost_eaten_{0};
  static Score* instance_;

private:
  Score() {};
public:
  static Score* getInstance() {
    if (!instance_)
      instance_ = new Score{};
    return instance_;
  }
  void handle(FruitEatenEvent& event);

  void reset();

  void update();

  void visit(CoinEatenEvent &event) override;

  void visit(FruitEatenEvent &event) override;

  void visit(GhostEatenEvent &event) override;

  void visit(PacmanDiesEvent &event) override;

  void visit(FrightenGhostsEvent &event) override;

  const int getValue() const {return value_;}

  void writeScoreToLeaderboard() const;

};

#endif // !SCORE_H
