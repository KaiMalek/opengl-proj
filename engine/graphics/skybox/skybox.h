#ifndef SKYBOX_H
#define SKYBOX_H

#include <string>
#include <vector>
#include <glad/glad.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../shaders/shaders.h"

class skybox {
private:
    unsigned int skybox_vao, skybox_vbo;
    unsigned int cubemap_texture;

    unsigned int load_cubemap(const std::vector<std::string>& faces);

public:
    skybox(const std::vector<std::string>& faces);
    ~skybox();

    void draw(const shader& shader, const glm::mat4& view_matrix, const glm::mat4& projection_matrix);
};

#endif