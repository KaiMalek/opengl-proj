#include "character.h"

character::character() {
    c_player_arm = new model("C:\\projects\\opengl-proj\\resources\\arm_model\\arm_model.obj");
    c_player_arm->set_model_scale(glm::vec3(0.02f));
    arm_offset = glm::vec3(0.f, 0.4f, 0.2f);
}

character::~character() {
    delete c_player_arm;
}

void character::set_arm_offset(const glm::vec3& offset) {
    arm_offset = offset;
}

glm::vec3 character::get_arm_offset() const {
    return arm_offset;
}
// keep this shit away from me... atleast the hands dont get seizures anymore am i right? ;)
void character::update(const camera& player_camera, float delta_time) {
    glm::vec3 camera_front = glm::normalize(player_camera.get_forward_vec());
    glm::vec3 camera_up = glm::normalize(player_camera.get_up_vec());
    glm::vec3 camera_right = glm::normalize(glm::cross(camera_front, camera_up));

    glm::vec3 camera_position = player_camera.get_position();
    glm::vec3 target_position = camera_position
        + player_camera.get_forward_vec() * 0.5f
        + player_camera.get_up_vec() * -0.5f
        + arm_offset;

    float interpolation_speed = 10.0f;

    glm::vec3 current_position = c_player_arm->get_model_position();
    glm::vec3 smoothed_position = current_position + (target_position - current_position) * interpolation_speed * delta_time;

    c_player_arm->set_model_position(smoothed_position);

    glm::mat4 rotation_matrix = glm::mat4(glm::vec4(camera_right, 0.0f),
        glm::vec4(camera_up, 0.0f),
        glm::vec4(-camera_front, 0.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    glm::mat4 model_rotation = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 final_rotation = rotation_matrix * model_rotation;

    c_player_arm->set_model_matrix(glm::translate(glm::mat4(1.0f), smoothed_position) * final_rotation);
}
