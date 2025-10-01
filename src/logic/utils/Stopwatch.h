//
// Created by joachimverleysen on 12/10/24.
//

#ifndef DOODLEJUMP_STOPWATCH_H
#define DOODLEJUMP_STOPWATCH_H


#include <chrono>
#include <thread>

class Stopwatch {
    static Stopwatch* instance_;
    Stopwatch() : last_time_(std::chrono::high_resolution_clock::now()) {}
public:
    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

    static Stopwatch* getInstance() {
        if (!instance_) {
            instance_ = new Stopwatch(); 
        }
        return instance_;
    }


    float getDeltaTime() {
        auto current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> delta = current_time - last_time_;
        last_time_ = current_time;
        return delta.count();
    }

    void capFramerate(float max_fps) {
        float frame_duration = 1.0f / max_fps;
        auto current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> delta = current_time - last_time_;

        if (delta.count() < frame_duration) {
            std::this_thread::sleep_for(
                std::chrono::duration<float>(frame_duration - delta.count())
            );
        }
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> last_time_;
};


#endif //DOODLEJUMP_STOPWATCH_H
