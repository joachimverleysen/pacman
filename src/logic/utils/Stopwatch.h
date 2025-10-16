#ifndef DOODLEJUMP_STOPWATCH_H
#define DOODLEJUMP_STOPWATCH_H

#include <chrono>
#include <thread>

class Stopwatch {
  static Stopwatch *instance_;
  Stopwatch() : last_time_(std::chrono::high_resolution_clock::now()) {}

public:
  Stopwatch(const Stopwatch &) = delete;
  Stopwatch &operator=(const Stopwatch &) = delete;

  static Stopwatch *getInstance() {
    if (!instance_) {
      instance_ = new Stopwatch();
    }
    return instance_;
  }

  float getDeltaTime();

  void capFramerate(float max_fps);

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> last_time_;
};

#endif // DOODLEJUMP_STOPWATCH_H
