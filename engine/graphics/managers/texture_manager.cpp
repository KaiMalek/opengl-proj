#include "texture_manager.h"
#include <iostream>

texture_manager& texture_manager::instance() {
    static texture_manager instance;
    return instance;
}

texture* texture_manager::load_texture(const std::string& name, const char* texture_path, const std::string& type = "diffuse") {
    if (textures.find(name) != textures.end())
        return textures[name];

    texture* new_texture = new texture(texture_path, type);
    if (new_texture && new_texture->get_id() != 0) {
        textures[name] = new_texture;
    }
    else {
        std::cerr << "Failed to load texture: " << texture_path << std::endl;
        delete new_texture;
        return nullptr;
    }

    return new_texture;
}


texture* texture_manager::get_texture(const std::string& name) const {
    auto it = textures.find(name);
    if (it != textures.end())
        return it->second;
    return nullptr;
}

void texture_manager::cleanup() {
    for (auto& tex : textures) {
        tex.second->shutdown();
        delete tex.second;
    }
    textures.clear();
}