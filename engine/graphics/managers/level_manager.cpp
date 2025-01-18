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
    c_model_simon->draw(shader);
    c_model_plat->draw(shader);
}

void level_manager::load_demo_level() {
    // just in case 
    models.clear();

    c_model_simon = new model("C:\\projects\\opengl-proj\\resources\\simon\\simon.obj");
    models.push_back(c_model_simon);
    c_model_simon->set_model_position(glm::vec3(0.f, 0.f, .0f));

    c_model_plat = new model("C:\\projects\\opengl-proj\\resources\\dust-world\\dust2.obj");
    models.push_back(c_model_plat);
    c_model_simon->set_model_position(glm::vec3(0.f, 0.f, .0f));
}