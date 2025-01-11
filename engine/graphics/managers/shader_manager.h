#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include "../shaders/shaders.h"

#include <string>
#include <unordered_map>

class shader_manager {
public:
    static shader_manager& instance();

    shader* load_shader(const std::string& name, const char* vertex_path, const char* fragment_path);
    shader* get_shader(const std::string& name) const;
    void cleanup();

private:
    shader_manager() = default;
    std::unordered_map<std::string, shader*> shaders;
};

#endif
