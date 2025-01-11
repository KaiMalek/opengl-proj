#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <unordered_map>
#include <memory>
#include "shader_manager.h"
#include "texture_manager.h"

class resource_manager {
public:
    static resource_manager& instance();
    shader* load_shader(const std::string& name, const char* vertex_path, const char* fragment_path);
    shader* get_shader(const std::string& name) const;

    texture* load_texture(const std::string& name, const char* texture_path, const std::string& type);
    texture* get_texture(const std::string& name) const;

    void cleanup();

private:
    resource_manager() = default;
};

#endif
