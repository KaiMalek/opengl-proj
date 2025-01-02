#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <direct.h>
#include "../engine/core/engine.h"

#define NODEFAULTLIB

int main() {
    engine c_engine;

    if (!c_engine.initialize(WIN_WIDTH, WIN_HEIGHT, WIN_NAME)) {
        std::cerr << "Engine initialization failed!" << std::endl;
        return -1;
    }

    c_engine.run();

    c_engine.shutdown();

    return 0;
}