#ifndef ENGINE_H
#define ENGINE_H

#include "window.h"
#include "timer.h"
#include "debug_menu/debug_menu.h"

#include "../graphics/shaders.h"
#include "../graphics/textures.h"
#include "../mesh/mesh.h"
#include "../world/coords.h"
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
private:
    window* c_window;
    timer* c_time;
    debug_menu* c_debug_menu;

    shader* c_shader;
    texture* c_texture;
    mesh* c_mesh;
    coords* c_coord;
    camera* c_camera;
};
#endif