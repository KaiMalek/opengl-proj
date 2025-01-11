#include "quad.h"

quad::quad() {
    GLfloat vertices[] = {
        // Positions        // Texture Coordinates
        1.0f,  1.0f, 0.0f,  1.0f, 1.0f,  // Top right
        1.0f, -1.0f, 0.0f,  1.0f, 0.0f,  // Bottom right
       -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,  // Bottom left
       -1.0f,  1.0f, 0.0f,  0.0f, 1.0f   // Top left 
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

quad::~quad() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void quad::set_position(float x, float y, float width, float height) {
    position = glm::vec3(x, y, 0.0f);
}

void quad::render(GLuint shader_program) {
    glUseProgram(shader_program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}
