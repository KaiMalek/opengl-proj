#include "interpolation.h"

template <typename T>
interpolation<T>::interpolation(float smoothing_factor)
    : smoothing_factor(smoothing_factor), current_state(T(0)) {
}

template <typename T>
void interpolation<T>::record_state(const T& state) {
    state_queue.push(state);
}

template <typename T>
T interpolation<T>::interpolate(float delta_time) {
    if (!state_queue.empty()) {
        T target_state = state_queue.front();
        state_queue.pop();

        current_state = glm::mix(current_state, target_state, smoothing_factor * delta_time);
    }
    return current_state;
}

template class interpolation<glm::vec3>;