#include "window.h"
#include <iostream>

GLFWwindow* window::m_window = nullptr;
int window::m_width = WIN_WIDTH;
int window::m_height = WIN_HEIGHT;
float window::m_aspectRatio = 16.0f / 9.0f;
glm::mat4 window::m_projectionMatrix = glm::mat4(1.0f);

window::~window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}

bool window::initialize(int width, int height, const char* title) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return false;
    }

    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    return true;
}

void window::shutdown() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void window::poll_events() {
    glfwPollEvents();
}

bool window::should_close() {
    return glfwWindowShouldClose(m_window);
}

void window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    m_width = width;
    m_height = height;
    window::calculate_aspect_ratio();
    glViewport(0, 0, width, height);
    window::adjust_projection();
}

void window::calculate_aspect_ratio() {
    if (m_height != 0) {
        m_aspectRatio = static_cast<float>(m_width) / static_cast<float>(m_height);
    }
}

void window::adjust_projection() {
    m_projectionMatrix = glm::ortho(-m_aspectRatio, m_aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
}

void window::fix_resolution() {
    adjust_projection();
}

void window::get_window_size(int& outWidth, int& outHeight) {
    outWidth = m_width;
    outHeight = m_height;
}

void window::set_window_size(int width, int height) {
    glfwSetWindowSize(m_window, width, height);
    m_width = width;
    m_height = height;
    calculate_aspect_ratio();
}

float window::get_aspect_ratio() {
    return m_aspectRatio;
}

glm::mat4 window::get_projection_matrix() {
    return m_projectionMatrix;
}
