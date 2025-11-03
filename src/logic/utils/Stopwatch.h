#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <thread>

class Stopwatch {
  static Stopwatch *instance_;
  Stopwatch() : last_time_(std::chrono::high_resolution_clock::now()) {}
  float delta_time_{0};

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

  void update();

  void capFramerate(float max_fps);

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> last_time_;
};

#endif // STOPWATCH_H
