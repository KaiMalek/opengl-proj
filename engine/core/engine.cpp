#include "engine.h"
#include <iostream>

engine::~engine() {
    shutdown();
}

bool engine::initialize(int width, int height, const char* title) {
    c_time = new timer();
    c_time->start();

    c_window = new window();
    if (!c_window->initialize(width, height, title)) {
        std::cerr << "Failed to initialize the window!" << std::endl;
        return false;
    }

    c_debug_menu = new debug_menu(c_window->get_window());

    c_shader = new shader("C:\\projects\\opengl-proj\\engine\\graphics\\shaders\\shader.vert", "C:\\projects\\opengl-proj\\engine\\graphics\\shaders\\shader.frag");
    if (!c_shader) {
        std::cerr << "Shader init failed!" << std::endl;
        return false;
    }

    glm::vec3 camera_pos = glm::vec3(0.0f, 1.0f, 3.0f);
    glm::vec3 up_direction = glm::vec3(0.0f, 1.0f, 0.0f);

    c_camera = new camera(camera_pos, up_direction, 45.0f, static_cast<float>(width) / height, 0.1f, 100.0f);
    if (!c_camera) {
        std::cerr << "Camera init failed!" << std::endl;
        return false;
    }

    c_level_manager = new level_manager();
    c_level_manager->load_demo_level();

    return true;
}
// fuck light, imma straight up get that shit from:
// https://github.com/VictorGordan/opengl-tutorials/tree/main/YoutubeOpenGL%209%20-%20Lighting TADA! blt
void engine::run() {
    c_window->fix_resolution();

    while (!c_window->should_close()) {
        c_time->update();
        double delta_time = c_time->get_delta_time();

        c_window->poll_events();
        c_camera->process_input(c_window->get_window(), delta_time);

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        c_shader->use();

        glm::mat4 projection = c_camera->get_projection_matrix();
        glm::mat4 view = c_camera->get_view_matrix();

        c_shader->set_mat4("projection", projection);
        c_shader->set_mat4("view", view);

        c_level_manager->draw_demo_level(*c_shader);

        c_debug_menu->render();

        glfwSwapBuffers(c_window->get_window());
    }
}

void engine::shutdown() {
    c_window->shutdown();
}