#ifndef LIGHTS_H
#define LIGHTS_H

#include <glm/glm.hpp>

class lights {
public:
    enum light_type {
        DIRECTIONAL,
        POINT,
        SPOT
    };

    lights(glm::vec3 position, glm::vec3 color, float intensity, light_type type);

    void set_position(glm::vec3 position);
    void set_color(glm::vec3 color);
    void set_intensity(float intensity);
    void set_type(light_type type);

    glm::vec3 get_position() const;
    glm::vec3 get_color() const;
    float get_intensity() const;
    light_type get_type() const;

private:
    glm::vec3 position;
    glm::vec3 color;
    float intensity;
    light_type type;
};

#endif