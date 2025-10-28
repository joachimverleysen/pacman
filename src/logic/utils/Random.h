#ifndef RANDOM_H
#define RANDOM_H
#include "Utils.h"
#include "chrono"
#include "random"
#include "stdexcept"
#include <algorithm>
#include <initializer_list>

class Random {
  std::mt19937 generator_;
  std::random_device rd;
  std::default_random_engine rng_ = std::default_random_engine{rd()};

  static Random *instance_;
  Random();

public:
  float getFloat(float min, float max);

  int getInt(int min, int max);

  template <typename T> T getOption(std::vector<T> &options) {
    int index = getInt(0, options.size());
    return options[index];
  }

  template <typename T> void shuffle(std::vector<T> &vec) {
std::shuffle(std::begin(vec), std::end(vec), rng_);
  }

  static Random *getInstance() {
    if (!instance_)
      instance_ = new Random;
    return instance_;
  }
  bool decide(float chance);

  int makeWeightedDecision(const std::vector<float> &weights);
};

#endif // RANDOM_H
