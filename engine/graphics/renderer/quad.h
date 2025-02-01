#ifndef QUAD_H
#define QUAD_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class quad {
public:
    quad();
    ~quad();

    void set_position(float x, float y, float z);
    void render(GLuint shader_program);

private:
    GLuint VAO, VBO;
    glm::vec3 position;
};

#endif