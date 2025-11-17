#include <memory>
#include <algorithm>
#include "Stopwatch.h"
Stopwatch *Stopwatch::instance_ = nullptr;

float Stopwatch::getDeltaTime() { return delta_time_; }

void Stopwatch::capFramerate(float max_fps) {
  float frame_duration = 1.0f / max_fps;
  auto current_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> delta = current_time - last_time_;

  if (delta.count() < frame_duration) {
    std::this_thread::sleep_for(
        std::chrono::duration<float>(frame_duration - delta.count()));
  }
}

void Stopwatch::updateTimers() {
  if (timers_.empty()) return;

  for (auto t : timers_) {
    t->decrease(delta_time_);
  }


  // Remove timers that are finished
  timers_.erase(std::remove_if(timers_.begin(), timers_.end(),
                               [](const std::shared_ptr<Timer> &timer) {
                                  return timer->seconds <= 0;
                              }),

                timers_.end()
                );
}
void Stopwatch::update() {
  auto current_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> delta = current_time - last_time_;
  last_time_ = current_time;
  delta_time_ = delta.count();
  updateTimers();
}

std::shared_ptr<Timer> Stopwatch::getNewTimer(float seconds) {
  auto timer = std::make_shared<Timer>(seconds);
  timers_.push_back(timer);
  return timer;
}
