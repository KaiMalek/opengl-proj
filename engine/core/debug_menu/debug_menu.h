#ifndef DEBUG_MENU_H
#define DEBUG_MENU_H

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "console.h"
#include "../variables.h"
#include "../../camera/camera.h"
#include "../../audio/audio.h"

class debug_menu {
public:
    debug_menu(GLFWwindow* window);
    void frame_render();
    void watermark();
    void render();
    ~debug_menu();
private:
    camera* c_camera;
    audio* c_audio;
};
#endif
