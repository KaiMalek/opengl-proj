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
    components();
    ~components();

    void initialize_text_rendering();
    void load_font(const std::string& font_path);
    void text(const std::string& text, float x, float y, float scale, glm::vec3 color);

private:
    shader* text_shader;
    GLuint VAO, VBO;
    std::map<char, Character> Characters;
};

#endif