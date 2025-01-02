#include "timer.h"
#include <iostream>

timer::timer() : delta_time(0.0f), elapsed_time(0.0f) {
    last_time = glfwGetTime();
}

void timer::start() {
    last_time = glfwGetTime();
    elapsed_time = 0.0f;
}

void timer::stop() {
}

void timer::update() {
    float currentTime = glfwGetTime();
    delta_time = currentTime - last_time;
    last_time = currentTime;
    elapsed_time += delta_time;
}

float timer::get_elapsed_time() const {
    return elapsed_time;
}

float timer::get_delta_time() const {
    return delta_time;
}
