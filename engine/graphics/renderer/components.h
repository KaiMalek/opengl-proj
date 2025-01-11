#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb/stb_image.h>

#include "../shaders/shaders.h"
#include "../textures.h"

struct Character {
    GLuint texture_id;
    glm::ivec2 size;
    glm::ivec2 bearing;
    GLuint advance;
};

class components {
public:
    components(const char* vertex, const char* fragment);
    ~components();

    void text(const std::string& text, float x, float y, float scale, glm::vec3 color);

private:
    void initialize_text_rendering(const char* vertex, const char* fragment);
    void load_font(const std::string& font_path);

    GLuint VAO, VBO;
    std::unordered_map<char, Character> Characters;
    shader* text_shader;
};


#endif