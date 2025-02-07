#include "shaders.h"
#include <iostream>
#include <fstream>
#include <sstream>

shader::shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    check_compile_errors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    check_compile_errors(fragment, "FRAGMENT");

    shader_id = glCreateProgram();
    glAttachShader(shader_id, vertex);
    glAttachShader(shader_id, fragment);
    glLinkProgram(shader_id);
    check_compile_errors(shader_id, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void shader::use() const {
    if (shader_id != 0) {
        glUseProgram(shader_id);
    }
    else {
        std::cerr << "Shader program not initialized correctly!" << std::endl;
    }
}

void shader::set_bool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(shader_id, name.c_str()), (int)value);
}

void shader::set_int(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(shader_id, name.c_str()), value);
}

void shader::set_float(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(shader_id, name.c_str()), value);
}

void shader::set_vec3(const std::string& name, glm::vec3 color) const {
    glUniform3f(glGetUniformLocation(shader_id, name.c_str()), color.x, color.y, color.z);
}

void shader::set_mat4(const std::string& name, glm::mat4 mat) const {
    glUniformMatrix4fv(glGetUniformLocation(shader_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void shader::check_compile_errors(GLuint shader, const std::string& type) const {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n";
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n";
        }
    }
}
