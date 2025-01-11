#include "engine.h"
#include <iostream>

engine::~engine() {
    shutdown();
}

bool engine::initialize(int width, int height, const char* title) {
    c_time = new timer();
    if (c_time)
        std::cout << "Timer initialized!" << std::endl;
    c_time->start();

    c_window = new window();
    if (!c_window->initialize(width, height, title)) {
        std::cerr << "Failed to initialize the window!" << std::endl;
        return false;
    } else std::cout << "c_window initialized" << std::endl;

    c_debug_menu = new debug_menu(c_window->get_window());

    c_shader = new shader(shader_vertex, shader_fragment);
    if (!c_shader) {
        std::cerr << "Shader init failed!" << std::endl;
        return false;
    }
    else {
        std::cout << "c_shader initialized" << std::endl;
    }

    text_shader = new shader(text_vertex, text_fragment);
    if (!text_shader) {
        std::cerr << "Text shader initialization failed!" << std::endl;
        return false;
    }
    std::cout << "Text shader initialized" << std::endl;

    c_comp = new components(text_vertex, text_fragment);
    if (!c_comp) {
        std::cerr << "Components init failed!" << std::endl;
        return false;
    }
    else {
        std::cout << "c_comp initialized" << std::endl;
    }

    glm::vec3 camera_pos = glm::vec3(0.0f, 1.0f, 3.0f);
    glm::vec3 up_direction = glm::vec3(0.0f, 1.0f, 0.0f);

    c_camera = new camera(camera_pos, up_direction, 45.0f, static_cast<float>(width) / height, 0.1f, 100.0f);
    if (!c_camera) {
        std::cerr << "Camera init failed!" << std::endl;
        return false;
    } else std::cout << "c_camera initialized" << std::endl;

    c_level_manager = new level_manager();
    if (!c_level_manager) {
        std::cerr << "Level manager init failed!" << std::endl;
        return false;
    } else std::cout << "c_level_manager initialized" << std::endl;

    c_level_manager->load_demo_level();

    std::cout << "\n" << shader_vertex << std::endl;
    std::cout << shader_fragment << std::endl;
    std::cout << text_vertex << std::endl;
    std::cout << text_fragment << std::endl;

    return true;
}
// fuck light, imma straight up get that shit from:
// https://github.com/VictorGordan/opengl-tutorials/tree/main/YoutubeOpenGL%209%20-%20Lighting TADA! blt
void engine::run() {
    c_window->fix_resolution();
    glfwSetKeyCallback(c_window->get_window(), c_window->fullscreen_callback);

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

        glm::mat4 text_projection = glm::ortho(5.0f, static_cast<float>(c_window->m_width), static_cast<float>(c_window->m_height), 0.0f, -1.0f, 1.0f);
        text_shader->use();
        text_shader->set_mat4("projection", text_projection);
        // waht hte fuck
        c_comp->text("fuck this shit", 10.0f, 10.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

        c_debug_menu->render();

        glfwSwapBuffers(c_window->get_window());
    }
}

void engine::shutdown() {
    c_window->shutdown();
}