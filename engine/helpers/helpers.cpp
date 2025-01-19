#include "helpers.h"

std::string helpers::vec3_to_string(const glm::vec3& vec) {
    std::ostringstream oss;
    oss << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return oss.str();
}