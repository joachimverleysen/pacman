#ifndef RANDOM_H
#define RANDOM_H
#include "random"
#include <algorithm>
#include <initializer_list>

class Random {
  std::mt19937 generator_;
  std::random_device rd;
  std::default_random_engine rng_ = std::default_random_engine{rd()};

  static Random *instance_;
  Random();

public:
  /// Returns random float within range
  float getFloat(float min, float max);

  /// Returns random int within range
  int getInt(int min, int max);

  /// Randomly picks an element from the vector
  template <typename T> T getOption(std::vector<T> &options) {
    int index = getInt(0, options.size());
    return options[index];
  }

  /// Randomly shuffles the vector
  template <typename T> void shuffle(std::vector<T> &vec) {
    std::shuffle(std::begin(vec), std::end(vec), rng_);
  }

  /// Singleton
  static Random *getInstance() {
    if (!instance_)
      instance_ = new Random;
    return instance_;
  }

  /// The chance that this returns true is <chance>
  bool decide(float chance);

  /// Makes a weighted decision by returning the corresponding index of the
  /// weight. Higher weights are more likely to be chosen.
  int makeWeightedDecision(const std::vector<float> &weights);
};

#endif // RANDOM_H
