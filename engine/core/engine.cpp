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

    c_texture = new texture("C:\\projects\\opengl-proj\\resources\\dev_512x512.jpg", "diffuse");
    if (!c_texture) {
        std::cerr << "Texture init failed!" << std::endl;
        return false;
    }

    glm::vec3 camera_pos = glm::vec3(0.0f, 1.0f, 3.0f);
    glm::vec3 up_direction = glm::vec3(0.0f, 1.0f, 0.0f);

    c_camera = new camera(camera_pos, up_direction, 45.0f, static_cast<float>(width) / height, 0.1f, 100.0f);
    if (!c_camera) {
        std::cerr << "Camera init failed!" << std::endl;
        return false;
    }

    std::vector<float> vertices = {
    // Front face
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // Top right front
     0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // Bottom right front
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // Bottom left front
    -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // Top left front
     // Back face
     0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // Top right back
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // Bottom right back
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // Bottom left back
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // Top left back
     // Left face
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // Top left front
    -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // Bottom left front
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // Bottom left back
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // Top left back
     // Right face
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // Top right front
     0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // Bottom right front
     0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // Bottom right back
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // Top right back
     // Top face
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // Top right front
    -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // Top left front
    -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // Top left back
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // Top right back
     // Bottom face
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // Bottom right front
    -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // Bottom left front
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // Bottom left back
     0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // Bottom right back
    };

    std::vector<unsigned int> indices = {
    0, 1, 3, 1, 2, 3,  // Front face
    4, 5, 7, 5, 6, 7,  // Back face
    8, 9, 11, 9, 10, 11, // Left face
    12, 13, 15, 13, 14, 15, // Right face
    16, 17, 19, 17, 18, 19, // Top face
    20, 21, 23, 21, 22, 23  // Bottom face
    };

    c_mesh = new mesh(vertices, indices);
    c_mesh->initialize();
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

        model = glm::rotate(glm::mat4(1.0f), glm::radians(variables::cube_angle), glm::vec3(1.0f, 1.0f, 0.0f));
        variables::cube_angle += variables::cube_rotate_speed;
        c_shader->set_mat4("model", model);

        c_texture->bind();
        c_texture->tex_unit(*c_shader, "texture1", 0);

        c_mesh->draw();

        c_debug_menu->render();

        glfwSwapBuffers(c_window->get_window());
    }
}

void engine::shutdown() {
    c_window->shutdown();
    c_mesh->shutdown();
    c_texture->shutdown();
}