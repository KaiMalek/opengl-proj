#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../core/variables.h"

class camera {
public:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    bool m_cursor_locked = false;

    float m_yaw;
    float m_pitch;
    float m_movement_speed;
    float m_mouse_sensitivity;
    float m_fov;
    float m_aspect;
    float m_near;
    float m_far;
    double lastX, lastY;

    glm::mat4 m_projection;
    glm::mat4 m_view;

    glm::quat m_orientation;

    camera(glm::vec3 position, glm::vec3 up, float fov, float aspect, float near, float far);

    glm::mat4 get_view_matrix();
    glm::mat4 get_projection_matrix();
    glm::quat get_orientation() const;

    void move(glm::vec3 delta);
    void rotate(float pitch, float yaw);
    void update_orientation();
    void update();
    void update_vectors();

    void process_keyboard_input(GLFWwindow* window, double deltaTime);
    void unlock_cursor(GLFWwindow* window);
    void process_mouse_input(GLFWwindow* window);
    void process_input(GLFWwindow* window, double deltaTime);
    void lock_cursor(GLFWwindow* window);
    glm::vec3 get_position() const {
        return m_position;
    }
    glm::vec3 get_forward_vec() const {
        return glm::normalize(m_front);
    }
    glm::vec3 get_up_vec() const {
        return glm::normalize(m_up);
    }

private:
};

#endif
