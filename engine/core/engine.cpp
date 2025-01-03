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

    c_shader = new shader("C:\\projects\\opengl-proj\\resources\\shader.vert", "C:\\projects\\opengl-proj\\resources\\shader.frag");
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

    std::string model_path = "C:\\projects\\opengl-proj\\resources\\world_model.obj";

    c_model = new model(model_path);
    if (!c_model) {
        std::cerr << "Model init failed!" << std::endl;
        return false;
    }
    return true;
}
// fuck light, imma straight up get that shit from:
// https://github.com/VictorGordan/opengl-tutorials/tree/main/YoutubeOpenGL%209%20-%20Lighting TADA! blt
void engine::run() {
    c_window->fix_resolution();

    glm::mat4 projection = c_camera->get_projection_matrix();
    glm::mat4 view = c_camera->get_view_matrix();

    glm::mat4 model = glm::mat4(1.0f);

    while (!c_window->should_close()) {
        c_time->update();
        double delta_time = c_time->get_delta_time();

        c_window->poll_events();
        c_camera->process_input(c_window->get_window(), delta_time);

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        c_shader->use();

        projection = c_camera->get_projection_matrix();
        view = c_camera->get_view_matrix();

        c_shader->set_mat4("projection", projection);
        c_shader->set_mat4("view", view);

        // earths rotation axial tilt {0.398, 0, 0.917}
        // R = (sin(23.5deg), 0, cos(23.5deg)) 23.5 deg relative to the plane of its orbit around the sun
        model = glm::rotate(glm::mat4(1.0f), glm::radians(variables::cube_angle), glm::vec3(0.398f, 0.917f, 0.f));
        variables::cube_angle += variables::cube_rotate_speed;
        c_shader->set_mat4("model", model);

        c_model->draw(*c_shader);

        c_debug_menu->render();

        glfwSwapBuffers(c_window->get_window());
    }
}

void engine::shutdown() {
    c_window->shutdown();
}