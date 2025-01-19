#ifndef SKYBOX_H
#define SKYBOX_H

#include <string>
#include <vector>
#include <glad/glad.h>
#include <stb/stb_image.h>

#include "../shaders/shaders.h"

class skybox {
public:
    skybox();
    ~skybox();
    bool initialize(const std::vector<std::string>& faces);
    void render(const shader& shader);

private:
    GLuint texture_id;
    GLuint vao;
    GLuint vbo;
};

#endif