#include "shader_manager.h"
#include <iostream>

shader_manager& shader_manager::instance() {
    std::cout << "Shader manager initialized." << std::endl;
    static shader_manager instance;
    return instance;
}

shader* shader_manager::load_shader(const std::string& name, const char* vertex_path, const char* fragment_path) {
    if (shaders.find(name) != shaders.end())
        return shaders[name];

    shader* new_shader = new shader(vertex_path, fragment_path);
    if (new_shader)
        shaders[name] = new_shader;
    else
        std::cerr << "Failed to load shader: " << name << std::endl;

    return new_shader;
}

shader* shader_manager::get_shader(const std::string& name) const {
    auto it = shaders.find(name);
    if (it != shaders.end())
        return it->second;
    return nullptr;
}

void shader_manager::cleanup() {
    for (auto& sh : shaders) {
        delete sh.second;
    }
    shaders.clear();
}