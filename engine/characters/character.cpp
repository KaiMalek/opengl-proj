#include "character.h"

character::character()
    : arm_interpolation(64.f), arm_offset(glm::vec3(0.f, -0.1f, 0.2f)) {
    c_player_arm = new model("C:\\projects\\opengl-proj\\resources\\arm_model\\arm_model.obj");
    c_player_arm->set_model_scale(glm::vec3(0.02f));
    c_player_arm->set_model_position(glm::vec3(0.f, 0.f, 0.f));
}

character::~character() {
    delete c_player_arm;
}
// literally recode #13, arms getting flat when looking up/down
void character::update(const camera& player_camera, float delta_time) {
    glm::vec3 camera_front = glm::normalize(player_camera.get_forward_vec());
    glm::vec3 camera_up = glm::normalize(player_camera.get_up_vec());
    glm::vec3 camera_right = glm::normalize(glm::cross(camera_front, camera_up));
    glm::vec3 camera_position = player_camera.get_position();

    glm::vec3 target_position = camera_position
        + camera_front * arm_offset.z
        + camera_up * arm_offset.y
        + camera_right * arm_offset.x;

    arm_interpolation.record_state(target_position);
    glm::vec3 smoothed_position = arm_interpolation.interpolate(delta_time);

    glm::mat4 rotation_matrix = glm::mat4(
        glm::vec4(camera_right, 0.0f),
        glm::vec4(camera_up, 0.0f),
        glm::vec4(-camera_front, 0.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );

    glm::mat4 model_rotation = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 final_matrix = glm::translate(glm::mat4(1.0f), smoothed_position) * rotation_matrix * model_rotation;

    c_player_arm->set_model_matrix(final_matrix);
}

void character::set_arm_offset(const glm::vec3& offset) {
    arm_offset = offset;
}

glm::vec3 character::get_arm_offset() const {
    return arm_offset;
}
