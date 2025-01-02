#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define WIN_HEIGHT 720
#define WIN_WIDTH 1280
#define WIN_NAME "Test Window"

class window {
public:
    window() = default;
    ~window();

    static bool initialize(int width, int height, const char* title);
    static void shutdown();
    static void poll_events();
    static bool should_close();
    static GLFWwindow* get_window() { return m_window; }

    static void fix_resolution();
    static void get_window_size(int& outWidth, int& outHeight);
    static void set_window_size(int width, int height);
    static float get_aspect_ratio();

    static glm::mat4 get_projection_matrix();

    static int m_width, m_height;
private:
    static GLFWwindow* m_window;
    static float m_aspectRatio;
    static glm::mat4 m_projectionMatrix;

    static void calculate_aspect_ratio();
    static void adjust_projection();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
#endif