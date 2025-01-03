#define STB_IMAGE_IMPLEMENTATION
#include "textures.h"
#include <iostream>

texture::texture(const std::string& path, const std::string& type) {
    this->path = path;
    this->type = type;
    load_texture(path);
}

void texture::load_texture(const std::string& path) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format = (nrChannels == 3) ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        std::cout << "STB Image Error: " << stbi_failure_reason() << std::endl;
        stbi_image_free(data);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

void texture::tex_unit(shader& shader, const char* uniform, GLuint unit) {
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    shader.use();
    glUniform1i(texUni, unit);
}

void texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, ID);
}

void texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void texture::shutdown() const {
    glDeleteTextures(1, &ID);
}
