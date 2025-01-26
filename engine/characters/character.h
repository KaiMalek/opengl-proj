#ifndef CHARACTER_H
#define CHARACTER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "../graphics/models/models.h"
#include "../camera/camera.h"
#include "../interpolation/interpolation.h"

class character {
public:
    character();
    ~character();

    void update(const camera& player_camera, float delta_time);

    void set_arm_offset(const glm::vec3& offset);

    glm::vec3 get_arm_offset() const;

    model* c_player_arm;

private:
    interpolation<glm::vec3> arm_interpolation;
    glm::vec3 arm_offset;
};

#endif
