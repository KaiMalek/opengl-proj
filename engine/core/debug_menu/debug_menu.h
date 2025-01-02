#ifndef DEBUG_MENU_H
#define DEBUG_MENU_H

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include "../variables.h"

class debug_menu {
public:
    debug_menu(GLFWwindow* window);
    void frame_render();
    void logic();
    void render();
    ~debug_menu();
private:
};
#endif
