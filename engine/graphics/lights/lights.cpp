#include "lights.h"

lights::lights(glm::vec3 position, glm::vec3 color, float intensity, light_type type)
    : position(position), color(color), intensity(intensity), type(type) {
}

void lights::set_position(glm::vec3 position) {
    this->position = position;
}

void lights::set_color(glm::vec3 color) {
    this->color = color;
}

void lights::set_intensity(float intensity) {
    this->intensity = intensity;
}

void lights::set_type(light_type type) {
    this->type = type;
}

glm::vec3 lights::get_position() const {
    return position;
}

glm::vec3 lights::get_color() const {
    return color;
}

float lights::get_intensity() const {
    return intensity;
}

lights::light_type lights::get_type() const {
    return type;
}