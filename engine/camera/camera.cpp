#include "camera.h"

camera::camera(glm::vec3 position, glm::vec3 up, float fov, float aspect, float near, float far)
    : m_position(position), m_up(up), m_fov(fov), m_aspect(aspect), m_near(near), m_far(far),
    m_yaw(-90.0f), m_pitch(0.0f), m_movement_speed(8.0f), m_mouse_sensitivity(0.1f), m_cursor_locked(false)
{
    m_front = glm::vec3(0.0f, 0.0f, -1.0f);

    update_vectors();
    m_projection = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
    m_view = glm::lookAt(m_position, m_position + m_front, m_up);

    lastX = 0.0f;
    lastY = 0.0f;
}

glm::mat4 camera::get_view_matrix() {
    return m_view;
}

glm::mat4 camera::get_projection_matrix() {
    return m_projection;
}

void camera::move(glm::vec3 delta) {
    m_position += delta;
    update();
}

void camera::rotate(float pitch, float yaw) {
    m_pitch += pitch;
    m_yaw += yaw;

    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front = glm::normalize(direction);
    update();
}

void camera::update() {
    m_view = glm::lookAt(m_position, m_position + m_front, m_up);
}

void camera::update_vectors() {
    m_right = glm::normalize(glm::cross(m_front, m_up));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

void camera::process_keyboard_input(GLFWwindow* window, double deltaTime) {
    float velocity = m_movement_speed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        velocity = (m_movement_speed * deltaTime) / 2;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        move(m_front * velocity);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        move(-m_front * velocity);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_position -= glm::normalize(glm::cross(m_front, m_up)) * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_position += glm::normalize(glm::cross(m_front, m_up)) * velocity;
}

void camera::process_mouse_input(GLFWwindow* window) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !m_cursor_locked) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        m_cursor_locked = true;

        glfwGetCursorPos(window, &lastX, &lastY);
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && m_cursor_locked) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        m_cursor_locked = false;
    }

    if (m_cursor_locked) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        float xOffset = xpos - lastX;
        float yOffset = lastY - ypos;

        lastX = xpos;
        lastY = ypos;

        xOffset *= m_mouse_sensitivity;
        yOffset *= m_mouse_sensitivity;

        rotate(yOffset, xOffset);
    }
}
// very gheto solution for insert open/close menu, but it is what it is lmao
void camera::process_input(GLFWwindow* window, double deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_INSERT) == GLFW_PRESS && !variables::was_insert_pressed) {
        variables::menu_open = !variables::menu_open;

        if (variables::menu_open) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwGetCursorPos(window, &lastX, &lastY);
        }
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPos(window, lastX, lastY);
        }

        variables::was_insert_pressed = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_INSERT) == GLFW_RELEASE) {
        variables::was_insert_pressed = false;
    }

    if (!variables::menu_open || variables::enable_movement) {
        process_keyboard_input(window, deltaTime);
        process_mouse_input(window);
    }
}
