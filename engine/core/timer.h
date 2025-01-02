#ifndef TIMER_H
#define TIMER_H

#include <GLFW/glfw3.h>

class timer {
public:
    timer();

    void start();
    void stop();
    void update();
    float get_elapsed_time() const;
    float get_delta_time() const;
private:
    float last_time;
    float delta_time;
    float elapsed_time;
};

#endif
