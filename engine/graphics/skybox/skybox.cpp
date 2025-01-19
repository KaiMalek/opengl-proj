#include "skybox.h"
#include <iostream>

skybox::skybox() : texture_id(0), vao(0), vbo(0) {}

skybox::~skybox() {
    if (texture_id) glDeleteTextures(1, &texture_id);
    if (vao) glDeleteVertexArrays(1, &vao);
    if (vbo) glDeleteBuffers(1, &vbo);
}

bool skybox::initialize(const std::vector<std::string>& faces) {
    const float size = 100.0f;

    float skybox_vertices[] = {
        -size,  size, -size, -size, -size, -size, size, -size, -size, size, -size, -size,
        size,  size, -size, -size,  size, -size, -size, -size,  size, -size,  size,  size,
        -size,  size,  size, size, -size,  size, size,  size,  size, size, -size,  size,
        -size, -size,  size, -size,  size,  size, size,  size,  size, size, -size,  size,
        -size,  size, -size, size,  size, -size, size,  size,  size, size,  size,  size,
        -size, -size, -size, -size, -size,  size, size, -size, -size, size, -size, -size
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skybox_vertices), &skybox_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    stbi_set_flip_vertically_on_load(false);

    int width, height, nr_channels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nr_channels, 0);
        if (!data) {
            std::cerr << "Failed to load texture at: " << faces[i] << std::endl;
            return false;
        }
        GLenum format = (nr_channels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    return true;
}

void skybox::render(const shader& shader) {
    glDepthFunc(GL_LEQUAL);
    shader.use();
    shader.set_bool("skybox", 0);
    glBindVertexArray(vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}
