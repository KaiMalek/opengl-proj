#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texcoord;

out vec3 frag_normal;
out vec2 frag_texcoord;
out vec3 frag_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    frag_position = vec3(model * vec4(a_pos, 1.0));
    frag_normal = mat3(transpose(inverse(model))) * a_normal;
    frag_texcoord = a_texcoord;

    gl_Position = projection * view * vec4(frag_position, 1.0);
}
