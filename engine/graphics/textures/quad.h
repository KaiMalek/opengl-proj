#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

class quad {
public:
    quad();
    ~quad();

    void render(GLuint shader_program);
    void set_position(float x, float y, float width, float height);

private:
    GLuint VAO, VBO;
    glm::vec3 position;
};
