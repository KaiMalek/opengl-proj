#include "level_manager.h"
#include <iostream>

std::vector<std::string> skybox_faces = {
    "path/to/skybox/right.jpg",
    "path/to/skybox/left.jpg",
    "path/to/skybox/top.jpg",
    "path/to/skybox/bottom.jpg",
    "path/to/skybox/front.jpg",
    "path/to/skybox/back.jpg"
};

level_manager::level_manager() {
}

level_manager::~level_manager() {
    for (auto& m : models) {
        delete m;
    }
    models.clear();
}

void level_manager::draw_demo_level(shader& shader) {
    c_model_world->draw(shader);
    c_model_basement->draw(shader);
}

void level_manager::load_demo_level() {
    // just in case 
    models.clear();

    c_model_world = new model("C:\\projects\\opengl-proj\\resources\\world_model.obj");
    models.push_back(c_model_world);
    c_model_world->set_model_position(glm::vec3(0.f, 1.f, .0f));

    c_model_basement = new model("C:\\projects\\opengl-proj\\resources\\cool\\basement.obj");
    models.push_back(c_model_basement);
}
