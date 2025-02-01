#ifndef CUBE_H
#define CUBE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class cube {
public:
    cube();
    ~cube();

    void set_position(float x, float y, float z);
    void set_scale(float scale);
    void render(GLuint shader_program);

private:
    GLuint VAO, VBO;
    glm::vec3 position;
    float scale;
};

#endif