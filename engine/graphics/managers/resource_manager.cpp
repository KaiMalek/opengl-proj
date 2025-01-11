#include "resource_manager.h"
#include <iostream>

resource_manager& resource_manager::instance() {
    static resource_manager instance;
    return instance;
}

shader* resource_manager::load_shader(const std::string& name, const char* vertex_path, const char* fragment_path) {
    return shader_manager::instance().load_shader(name, vertex_path, fragment_path);
}

shader* resource_manager::get_shader(const std::string& name) const {
    return shader_manager::instance().get_shader(name);
}

texture* resource_manager::load_texture(const std::string& name, const char* texture_path, const std::string& type) {
    return texture_manager::instance().load_texture(name, texture_path, type);
}

texture* resource_manager::get_texture(const std::string& name) const {
    return texture_manager::instance().get_texture(name);
}

void resource_manager::cleanup() {
    shader_manager::instance().cleanup();
    texture_manager::instance().cleanup();
}