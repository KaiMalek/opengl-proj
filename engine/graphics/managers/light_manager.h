#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

#include "../lights/lights.h"
#include "../shaders/shaders.h"
#include <vector>
#include <memory>
#include <iostream>

class shader;

class light_manager {
public:
    light_manager();
    ~light_manager();

    void add_light(glm::vec3 position, glm::vec3 color, float intensity, lights::light_type type);
    void render_lights(shader& shader);

private:
    std::vector<std::unique_ptr<lights>> light;
};

#endif