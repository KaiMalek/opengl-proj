#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <unordered_map>
#include "../textures/textures.h"

class texture_manager {
public:
    static texture_manager& instance();

    texture* load_texture(const std::string& name, const char* texture_path, const std::string& type);
    texture* get_texture(const std::string& name) const;
    void cleanup();

private:
    texture_manager() = default;
    std::unordered_map<std::string, texture*> textures;
};

#endif
