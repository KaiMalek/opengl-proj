#ifndef TEXTURE_H
#define TEXTURE_H

#include <stb/stb_image.h>
#include <string>
#include "shaders/shaders.h"

class texture {
public:
    GLuint ID;
    std::string type;
    std::string path;

    texture(const std::string& path, const std::string& type);
    void load_texture(const std::string& path);
    void tex_unit(shader& shader, const char* uniform, GLuint unit);
    void bind() const;
    void unbind() const;
    void shutdown() const;
};

#endif

