#ifndef SCORE_H
#include <iostream>
#include <algorithm>
#include "entity/layout/Text.h"
#include "utils/Stopwatch.h"

class FruitEatenEvent;
class FrightenGhostsEvent;

class Score : public Entity {
  std::shared_ptr<Text> display_;
  // todo extract constants to Config
  int value{0};
  int coin_eaten_modifier_{7};
  int ghost_eaten_modifier_{300};
  int fruit_eaten_modifier_{60};
  float time_since_last_coin_{0};
  float time_since_ghost_eaten_{0};

public:
  Score() {};
  Score(std::shared_ptr<Text> text_entity)
    : display_(text_entity) {}

  void handle(FruitEatenEvent& event);

  void update() override;

  void handle(CoinEatenEvent& event);

  void handle(GhostEatenEvent& event);

  void handle(FrightenGhostsEvent& event);

  const int getValue() const {return value;}

  EntityType getType() const override {return EntityType::None;};
};

#endif // !SCORE_H
