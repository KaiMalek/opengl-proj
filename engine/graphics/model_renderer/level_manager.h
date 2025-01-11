#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <vector>
#include <string>
#include "models.h"
#include "../../core/variables.h"
#include "../../camera/camera.h"

class level_manager {
public:
    level_manager();
    ~level_manager();

    void draw_demo_level(shader& shader);

    void load_demo_level();

private:
    std::vector<model*> models;

    model* c_model_world;
    model* c_model_basement;
    model* c_model_simon;
};


#endif