#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <thread>
#include <vector>
#include <memory>

struct Timer {
  Timer(float mili) : seconds(mili) {}
  float seconds;
  void decrease(float mili) { seconds -= mili; }
  bool done() const { return seconds <= 0; }
};

class Stopwatch {
  static Stopwatch *instance_;
  Stopwatch() : last_time_(std::chrono::high_resolution_clock::now()) {}
  float delta_time_{0};
  std::vector<std::shared_ptr<Timer>> timers_{};

public:
  Stopwatch(const Stopwatch &) = delete;
  Stopwatch &operator=(const Stopwatch &) = delete;

  /// Singleton
  static Stopwatch *getInstance() {
    if (!instance_) {
      instance_ = new Stopwatch();
    }
    return instance_;
  }

  /// Returns delta time (time between last time and now)
  float getDeltaTime();

  /// Creates a timer
  std::shared_ptr<Timer> getNewTimer(float seconds);
  void update();

  /// Caps the framerate
  void capFramerate(float max_fps);

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> last_time_;

  void updateTimers();
};

#endif // STOPWATCH_H
