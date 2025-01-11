#ifndef ENGINE_H
#define ENGINE_H

#include "window.h"
#include "timer.h"
#include "debug_menu/debug_menu.h"

#include "../graphics/managers/resource_manager.h"
#include "../graphics/managers/level_manager.h"

#include "../graphics/textures/quad.h"

#include "../mesh/mesh.h"
#include "../coordinates/coords.h"
#include "../camera/camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class engine {
public:
    engine() = default;
    ~engine();

    bool initialize(int width, int height, const char* title);
    void run();
    void shutdown();

    // vertex/fragment paths
    const char* shader_vertex = "engine/graphics/shaders/shader.vert";
    const char* shader_fragment = "engine/graphics/shaders/shader.frag";

    const char* texture_vertex = "engine/graphics/textures/texture_shader.vert";
    const char* texture_fragment = "engine/graphics/textures/texture_shader.frag";
private:
    window* c_window;
    timer* c_time;
    debug_menu* c_debug_menu;

    quad* c_quad;

    resource_manager* c_resource;
    level_manager* c_level_manager;

    coords* c_coord;
    camera* c_camera;
};
#endif