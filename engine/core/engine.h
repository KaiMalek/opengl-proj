#ifndef ENGINE_H
#define ENGINE_H

#include "window.h"
#include "timer.h"
#include "debug_menu/debug_menu.h"
#include "../helpers/helpers.h"

#include "../graphics/skybox/skybox.h"
#include "../graphics/managers/resource_manager.h"
#include "../graphics/managers/level_manager.h"
#include "../graphics/renderer/quad.h"
#include "../graphics/managers/light_manager.h"
#include "../mesh/mesh.h"

#include "../coordinates/coords.h"
#include "../camera/camera.h"

#include "../audio/audio.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../graphics/renderer/cube.h"

class engine {
public:
    engine() = default;
    ~engine();

    bool initialize(int width, int height, const char* title);
    void run();
    void process_console();
    void shutdown();

    // vertex/fragment paths
    const char* shader_vertex = "engine/graphics/shaders/shader.vert";
    const char* shader_fragment = "engine/graphics/shaders/shader.frag";

    const char* texture_vertex = "engine/graphics/renderer/texture_shader.vert";
    const char* texture_fragment = "engine/graphics/renderer/texture_shader.frag";

    const char* skybox_vertex = "engine/graphics/skybox/skybox_shader.vert";
    const char* skybox_fragment = "engine/graphics/skybox/skybox_shader.frag";

    const char* light_vertex = "engine/graphics/lights/light_shader.vert";
    const char* light_fragment = "engine/graphics/lights/light_shader.frag";

    std::vector<std::string> skybox_faces = {
    "C:\\projects\\opengl-proj\\resources\\skybox_main\\sky_rt0001.bmp", "C:\\projects\\opengl-proj\\resources\\skybox_main\\sky_lf0001.bmp", "C:\\projects\\opengl-proj\\resources\\skybox_main\\sky_up0001.bmp",
    "C:\\projects\\opengl-proj\\resources\\skybox_main\\sky_dn0001.bmp", "C:\\projects\\opengl-proj\\resources\\skybox_main\\sky_ft0001.bmp", "C:\\projects\\opengl-proj\\resources\\skybox_main\\sky_bk0001.bmp"
    };
private:
    window* c_window;
    timer* c_time;
    debug_menu* c_debug_menu;
    console* c_console;
    helpers* c_helper;

    skybox* c_skybox;
    resource_manager* c_resource;
    level_manager* c_level_manager;
    light_manager* c_light_manager;

    cube* c_cube;

    coords* c_coord;
    camera* c_camera;

    audio* c_audio;
};
#endif