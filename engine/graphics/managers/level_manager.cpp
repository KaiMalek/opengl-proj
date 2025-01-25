#include "level_manager.h"
#include <iostream>

level_manager::level_manager() {
    c_character = new character();
}

level_manager::~level_manager() {
    for (auto& m : models) {
        delete m;
    }
    models.clear();
    delete c_character;
}

void level_manager::draw_demo_level(shader& shader) {
    c_model_player->draw(shader);
    c_model_player2->draw(shader);
    c_model_radio->draw(shader);
    c_model_world->draw(shader);
    c_character->c_player_arm->draw(shader);
}

void level_manager::load_demo_level() {
    // just in case 
    models.clear();
    // thank you some unknown dude who i found the models from on github :)
    c_model_player = new model("C:\\projects\\opengl-proj\\resources\\player\\T.obj");
    models.push_back(c_model_player);
    c_model_player->set_model_position(glm::vec3(-15.0f, 3.21f, 20.0f));
    c_model_player->set_model_scale(glm::vec3(0.025f));

    c_model_player2 = new model("C:\\projects\\opengl-proj\\resources\\simon\\simon_body.obj");
    models.push_back(c_model_player2);
    c_model_player2->set_model_position(glm::vec3(-19.0f, 3.21f, 20.0f));
    c_model_player2->set_model_scale(glm::vec3(0.0248f));

    c_model_radio = new model("C:\\projects\\opengl-proj\\resources\\soviet-radio\\radio.obj");
    models.push_back(c_model_radio);
    c_model_radio->set_model_position(glm::vec3(-43.0539f, 4.90f, 8.15248f));
    c_model_radio->set_model_scale(glm::vec3(2.f));

    c_model_world = new model("C:\\projects\\opengl-proj\\resources\\dust-world\\dust2.obj");
    models.push_back(c_model_world);
    c_model_world->set_model_position(glm::vec3(0.f, 0.f, .0f));

    models.push_back(c_character->c_player_arm);
}

void level_manager::update(camera& player_camera, float delta_time) {
    c_character->update(player_camera, delta_time);
}
