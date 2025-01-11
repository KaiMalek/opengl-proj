#ifndef ENGINE_H
#define ENGINE_H

#include "window.h"
#include "timer.h"
#include "debug_menu/debug_menu.h"

#include "../graphics/shaders/shaders.h"
#include "../graphics/textures.h"
#include "../graphics/model_renderer/level_manager.h"
#include "../graphics/renderer/components.h"

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


    float last_frame = 0.0f;

    // vertex/fragment paths
    const char* text_vertex = "engine/graphics/renderer/text_shader.vert";
    const char* text_fragment = "engine/graphics/renderer/text_shader.frag";

    const char* shader_vertex = "engine/graphics/shaders/shader.vert";
    const char* shader_fragment = "engine/graphics/shaders/shader.frag";
private:
    window* c_window;
    timer* c_time;
    debug_menu* c_debug_menu;

    shader* c_shader;
    shader* text_shader;
    components* c_comp;
    level_manager* c_level_manager;

    coords* c_coord;
    camera* c_camera;
};
#endif