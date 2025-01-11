#include "level_manager.h"
#include <iostream>

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
    c_model_simon->draw(shader);
}

void level_manager::load_demo_level() {
    // just in case 
    models.clear();

    c_model_world = new model("C:\\projects\\opengl-proj\\resources\\world\\world_model.obj");
    models.push_back(c_model_world);
    c_model_world->set_model_position(glm::vec3(0.f, 6.f, .0f));

    c_model_simon = new model("C:\\projects\\opengl-proj\\resources\\simon\\simon.obj");
    models.push_back(c_model_simon);
    c_model_simon->set_model_position(glm::vec3(10.f, 0.f, .0f));

    c_model_basement = new model("C:\\projects\\opengl-proj\\resources\\basement\\basement.obj");
    models.push_back(c_model_basement);
}
