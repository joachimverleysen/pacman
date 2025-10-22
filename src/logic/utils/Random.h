#ifndef RANDOM_H
#define RANDOM_H
#include "chrono"
#include "random"
#include "stdexcept"

class Random {
  std::mt19937 generator;

public:
  Random() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
  }
  float getFloat(float min, float max);
  ;
  int getInt(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
  };
  bool decide(float chance);

  int makeWeightedDecision(const std::vector<float> &weights);
};

#endif // RANDOM_H
