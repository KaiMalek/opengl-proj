#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <glm/glm.hpp>

#include <deque>
#include <chrono>
#include <queue>

template <typename T>
class interpolation {
public:
    explicit interpolation(float smoothing_factor);

    void record_state(const T& state);

    T interpolate(float delta_time);

private:
    float smoothing_factor;
    std::queue<T> state_queue;
    T current_state;
};

#endif
