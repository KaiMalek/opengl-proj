#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <vector>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/detail/type_vec.hpp>

#include "../graphics/shaders.h"

#define MAX_BONE_INFLUENCE 4

struct vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coords;
    glm::vec3 tangent;
    glm::vec3 bitangent;

    int bone_id[MAX_BONE_INFLUENCE];
    float bone_weight[MAX_BONE_INFLUENCE];
};

struct model_texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class mesh {
public:
    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<model_texture> textures;

    unsigned int VAO;

    mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices, std::vector<model_texture> textures);
    void draw(shader& shader);

private:
    unsigned int VBO, EBO;

    void setup_mesh();
};
#endif
