#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <vector>
#include <string>
#include "../models/models.h"
#include "../../core/variables.h"

class level_manager {
public:
    level_manager();
    ~level_manager();

    void draw_demo_level(shader& shader);

    void load_demo_level();

private:
    std::vector<model*> models;

    model* c_model_player;
    model* c_model_player2;
    model* c_model_radio;
    model* c_model_world;
};


#endif