#include "models.h"
#include <filesystem>

model::model(const std::string& path, bool gamma) : gamma_correction(gamma) {
    load_model(path);
}

void model::draw(shader& shader) {
    glm::mat4 model = model_matrix;
    shader.set_mat4("model", model);

    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].draw(shader);
}

void model::set_model_position(const glm::vec3& position) {
    model_position = position;
    model_matrix = glm::translate(glm::mat4(1.f), position);
}

void model::set_model_scale(const glm::vec3& scale) {
    model_scale = scale;
    model_matrix = glm::scale(model_matrix, scale);
}

void model::load_model(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));
    process_node(scene->mRootNode, scene);
}

void model::process_node(aiNode* node, const aiScene* scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(process_mesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        process_node(node->mChildren[i], scene);
    }
}

mesh model::process_mesh(aiMesh* ai_mesh, const aiScene* scene) {
    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<model_texture> textures;

    for (unsigned int i = 0; i < ai_mesh->mNumVertices; i++)
    {
        vertex vertex;
        glm::vec3 vector;

        vector.x = ai_mesh->mVertices[i].x;
        vector.y = ai_mesh->mVertices[i].y;
        vector.z = ai_mesh->mVertices[i].z;
        vertex.position = vector;

        if (ai_mesh->HasNormals())
        {
            vector.x = ai_mesh->mNormals[i].x;
            vector.y = ai_mesh->mNormals[i].y;
            vector.z = ai_mesh->mNormals[i].z;
            vertex.normal = vector;
        }

        if (ai_mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = ai_mesh->mTextureCoords[0][i].x;
            vec.y = ai_mesh->mTextureCoords[0][i].y;
            vertex.tex_coords = vec;

            vector.x = ai_mesh->mTangents[i].x;
            vector.y = ai_mesh->mTangents[i].y;
            vector.z = ai_mesh->mTangents[i].z;
            vertex.tangent = vector;

            vector.x = ai_mesh->mBitangents[i].x;
            vector.y = ai_mesh->mBitangents[i].y;
            vector.z = ai_mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        }
        else
            vertex.tex_coords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < ai_mesh->mNumFaces; i++)
    {
        aiFace face = ai_mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial* material = scene->mMaterials[ai_mesh->mMaterialIndex];
    std::vector<model_texture> diffuseMaps = load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<model_texture> specularMaps = load_material_textures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<model_texture> normalMaps = load_material_textures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<model_texture> heightMaps = load_material_textures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return mesh(vertices, indices, textures);
}

std::vector<model_texture> model::load_material_textures(aiMaterial* mat, aiTextureType type, const std::string& type_name) {
    std::vector<model_texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }

        if (!skip)
        {
            model_texture texture;
            texture.id = texture_from_file(str.C_Str(), directory);
            texture.type = type_name;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }

    return textures;
}

unsigned int model::texture_from_file(const char* path, const std::string& directory, bool gamma) {
    std::filesystem::path dirPath(directory);
    std::string textureDirectory = dirPath.parent_path().string();

    if (textureDirectory.back() != '/' && textureDirectory.back() != '\\')
        textureDirectory += '/';

    textureDirectory += path;
   
    unsigned int texture_id = 0;
    glGenTextures(1, &texture_id);

    int width, height, nr_components;
    unsigned char* data = stbi_load(textureDirectory.c_str(), &width, &height, &nr_components, 0);

    if (data)
    {
        GLenum format;
        if (nr_components == 1)
            format = GL_RED;
        else if (nr_components == 3)
            format = GL_RGB;
        else if (nr_components == 4)
            format = GL_RGBA;
        else
        {
            std::cerr << "Unsupported texture format with " << nr_components << " components!" << std::endl;
            stbi_image_free(data);
            return 0;
        }

        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cerr << "Texture failed to load at path: " << textureDirectory << std::endl;
        std::cerr << "STB Image Error: " << stbi_failure_reason() << std::endl;
        stbi_image_free(data);
        return 0;
    }

    return texture_id;
}