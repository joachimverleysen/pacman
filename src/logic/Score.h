#ifndef SCORE_H
#include <iostream>
#include <algorithm>
#include "entity/layout/Text.h"
#include "utils/Stopwatch.h"

class FruitEatenEvent;
class FrightenGhostsEvent;

class Score : public Entity {
  // todo extract constants to Config
  static Score* instance_;
  int value{0};
  int coin_eaten_modifier_{7};
  int ghost_eaten_modifier_{300};
  int fruit_eaten_modifier_{60};
  float time_since_last_coin_{0};
  float time_since_ghost_eaten_{0};

private:
  Score() = default;
public:
  static Score* getInstance() {
    if (!instance_)
      instance_ = new Score{};
    return instance_;
  }

  void handle(FruitEatenEvent& event);

  void update() override;

  void handle(CoinEatenEvent& event);

  void handle(GhostEatenEvent& event);

  void handle(FrightenGhostsEvent& event);

  const int getValue() const {return value;}

  EntityType getType() const override {return EntityType::None;};
};

#endif // !SCORE_H
