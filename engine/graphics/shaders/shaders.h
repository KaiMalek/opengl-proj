#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class shader {
public:
    GLuint ID;

    shader(const char* vertexPath, const char* fragmentPath);

    void use() const;
    void set_bool(const std::string& name, bool value) const;
    void set_int(const std::string& name, int value) const;
    void set_float(const std::string& name, float value) const;
    void set_vec3(const std::string& name, glm::vec3 color) const;
    void set_mat4(const std::string& name, glm::mat4 mat) const;
    GLuint get_id() const {
        return ID;
    }

private:
    void check_compile_errors(GLuint shader, const std::string& type) const;
};
#endif
