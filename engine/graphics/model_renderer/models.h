#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb/stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../mesh/mesh.h"
#include "../shaders.h"
#include "../../camera/camera.h"

#include <iostream>
#include <string>
#include <vector>

class model
{
public:
    glm::mat4 model_matrix;
    std::vector<model_texture> textures_loaded;
    std::vector<mesh> meshes;
    std::string directory;

    bool gamma_correction;

    model(const std::string& path, bool gamma = false);
    void draw(shader& shader);
    void set_model_position(const glm::vec3& position);

private:
    glm::vec3 model_position;

    void load_model(const std::string& path);
    void process_node(aiNode* node, const aiScene* scene);
    mesh process_mesh(aiMesh* ai_mesh, const aiScene* scene);
    std::vector<model_texture> load_material_textures(aiMaterial* mat, aiTextureType type, const std::string& type_name);
    unsigned int texture_from_file(const char* path, const std::string& directory, bool gamma = false);
};

#endif
