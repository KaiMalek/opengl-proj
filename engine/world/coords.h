#ifndef COORDS_H
#define COORDS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class coords {
public:
    static glm::mat4 get_model_matrix(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation_axis, float angle);
    static glm::mat4 get_view_matrix(glm::vec3 camera_position, glm::vec3 target, glm::vec3 up);
    static glm::mat4 get_projection_matrix(float fov, float aspect, float near, float far);
};

#endif
