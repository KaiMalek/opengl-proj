#include "light_manager.h"

light_manager::light_manager() {
    std::cout << "Light manager initialized." << std::endl;
}

light_manager::~light_manager() {
    light.clear();
}

void light_manager::add_light(glm::vec3 position, glm::vec3 color, float intensity, lights::light_type type) {
    auto new_light = std::unique_ptr<lights>(new lights{ position, color, intensity, type });

    light.push_back(std::move(new_light));
}

void light_manager::render_lights(shader& shader) {
    for (size_t i = 0; i < light.size(); i++) {
        const auto& light_ptr = light[i];
        std::string light_prefix = "lights[" + std::to_string(i) + "]";

        shader.set_vec3(light_prefix + ".position", light_ptr->get_position());
        shader.set_vec3(light_prefix + ".direction", glm::vec3{ 0.0f, -1.0f, 0.0f });
        shader.set_vec3(light_prefix + ".color", light_ptr->get_color());
        shader.set_float(light_prefix + ".intensity", light_ptr->get_intensity());
        shader.set_int(light_prefix + ".type", static_cast<int>(light_ptr->get_type()));
        shader.set_float(light_prefix + ".cut_off", glm::cos(glm::radians(12.5f)));
        shader.set_float(light_prefix + ".outer_cut_off", glm::cos(glm::radians(17.5f)));
    }
}