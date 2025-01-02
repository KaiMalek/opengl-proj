#include "coords.h"

glm::mat4 coords::get_model_matrix(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation_axis, float angle) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), rotation_axis);
    model = glm::scale(model, scale);
    return model;
}

glm::mat4 coords::get_view_matrix(glm::vec3 camera_position, glm::vec3 target, glm::vec3 up) {
    return glm::lookAt(camera_position, target, up);
}

glm::mat4 coords::get_projection_matrix(float fov, float aspect, float near, float far) {
    return glm::perspective(glm::radians(fov), aspect, near, far);
}
