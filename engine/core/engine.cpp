#include "engine.h"
#include <iostream>

// etymology engine

engine::~engine() {
    shutdown();
}

bool engine::initialize(int width, int height, const char* title) {
    c_time = new timer();
    if (c_time) {
        c_console->instance().log("Timer initialized");
        c_time->start();
    }

    c_window = new window();
    if (!c_window->initialize(width, height, title)) {
        std::cerr << "Failed to initialize the window!" << std::endl;
        return false;
    }
    c_console->instance().log("Window initialized");

    c_debug_menu = new debug_menu(c_window->get_window());

    c_resource = &resource_manager::instance();
    c_resource->load_shader("world_shader", shader_vertex, shader_fragment);
    c_resource->load_shader("skybox_shader", skybox_fragment, skybox_fragment);

    c_console->instance().log("Resource manager initialized");

    glm::vec3 camera_pos(0.0f, 1.0f, 3.0f);
    glm::vec3 up_direction(0.0f, 1.0f, 0.0f);

    c_camera = new camera(camera_pos, up_direction, 45.0f, static_cast<float>(width) / height, 0.1f, 100.0f);
    if (!c_camera) {
        std::cerr << "Camera init failed!" << std::endl;
        return false;
    }
    c_console->instance().log("Camera initialized");

    c_level_manager = new level_manager();
    if (!c_level_manager) {
        std::cerr << "Level manager init failed!" << std::endl;
        return false;
    }
    c_console->instance().log("Level manager initialized");

    c_audio = new audio();
    if (!c_audio) {
        std::cerr << "Audio init failed!" << std::endl;
        return false;
    }
    c_audio->init();
    c_console->instance().log("Audio initialized");

    c_skybox = new skybox(skybox_faces);
    if (!c_skybox) {
        std::cerr << "Skybox init failed!" << std::endl;
        return false;
    }
    c_console->instance().log("Skybox initialized");

    c_level_manager->load_demo_level();
    if (c_level_manager) {
        c_console->instance().log("Shader paths:");
        c_console->instance().log(shader_vertex);
        c_console->instance().log(shader_fragment);
        c_console->instance().log(skybox_vertex);
        c_console->instance().log(skybox_fragment);
        c_console->instance().log("Shaders initialized");
        c_console->instance().log("world_shader loaded");
    }

    return true;
}

void engine::run() {
    c_window->fix_resolution();
    glfwSetKeyCallback(c_window->get_window(), c_window->fullscreen_callback);

    shader* c_shader = c_resource->get_shader("world_shader");
    shader* c_skybox_shader = c_resource->get_shader("skybox_shader");
 
    while (!c_window->should_close()) {
        c_time->update();
        double delta_time = c_time->get_delta_time();

        c_level_manager->update(*c_camera, delta_time);

        c_window->poll_events();
        c_camera->process_input(c_window->get_window(), delta_time);

        glm::mat4 projection = c_camera->get_projection_matrix();
        glm::mat4 view = c_camera->get_view_matrix();

        glEnable(GL_DEPTH_TEST);
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // radio/audio sounds
        //c_audio->play_audio(variables::background_audio_file, variables::background_audio, 0.8f, true);
        // perfect sound for radio hehe
        c_audio->play_3d_audio("test.wav", glm::vec3(-43.0539f, 4.90f, 8.15248f), 0.007, 15.f, 0.1f);

        glm::vec3 listener_position = c_camera->get_position();
        glm::vec3 listener_forward = c_camera->get_forward_vec();
        glm::vec3 listener_up = c_camera->get_up_vec();

        c_audio->update(listener_position, listener_forward, listener_up);

        // draw skybox
        glDepthMask(GL_FALSE);
        c_skybox_shader->use();
        c_skybox->draw(*c_skybox_shader, view, projection);
        glDepthMask(GL_TRUE); 

        // render world
        c_shader->use();
        c_shader->set_mat4("projection", projection);
        c_shader->set_mat4("view", view);
        c_level_manager->draw_demo_level(*c_shader);

        // helpers
        std::cout << c_helper->vec3_to_string(c_camera->get_position()) << std::endl;

        process_console();
        c_debug_menu->render();

        glfwSwapBuffers(c_window->get_window());
    }
}

void engine::process_console() {
    console::instance().add_command("exit", [this]() {
        console::instance().log("exit", log_type::INFO);
        shutdown();
        });

    console::instance().add_command("clear", []() {
        console::instance().log("clear", log_type::INFO);
        console::instance().clear();
        });

    console::instance().add_command("help", []() {
        console::instance().log("help", log_type::INFO);
        console::instance().log("Etymology Engine commands: exit, clear, help.", log_type::INFO);
        });
}

void engine::shutdown() {
     c_window->shutdown();
}


//c_resource->load_shader("quad_shader", texture_vertex, texture_fragment);
//c_resource->load_texture("dev_texture", "resources/dev-textures/dev_512x512.jpg", "diffuse");

//c_quad = new quad();
//if (!c_quad) {
//    std::cerr << "quad pyzdiec" << std::endl;
//    return false;
//} 
//else std::cout << "quad zajebys" << std::endl;



        // testing resource manager for texture binding on a random object

        //quad_texture->bind();
        //quad_texture->tex_unit(*texture_shader, "texture1", 0);
        //
        //texture_shader->use();
        //c_quad->render(texture_shader->shader_id);



    //shader* texture_shader = c_resource->get_shader("quad_shader");
    //if (!c_shader || !texture_shader) {
    //    std::cout << "shaders got fucked" << std::endl;
    //}

    //texture* quad_texture = c_resource->get_texture("dev_texture");
    //if (!quad_texture) {
    //    std::cout << "pyzdiec" << std::endl;
    //}