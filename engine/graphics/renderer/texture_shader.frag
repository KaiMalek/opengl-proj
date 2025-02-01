#version 330 core

in vec3 frag_normal;
in vec2 frag_texcoord;
in vec3 frag_position;

out vec4 frag_color;

uniform sampler2D texture1;
uniform vec3 light_pos;
uniform vec3 light_color;
uniform vec3 view_pos;

void main() {
    vec3 normal = normalize(frag_normal);

    vec3 light_dir = normalize(light_pos - frag_position);

    // Diffuse lighting
    float diff = max(dot(normal, light_dir), 0.0);
    vec3 diffuse = diff * light_color;

    // Ambient lighting
    vec3 ambient = 0.2 * light_color;

    // Specular lighting
    vec3 view_dir = normalize(view_pos - frag_position);
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = spec * light_color;

    // Texture color
    vec3 tex_color = texture(texture1, frag_texcoord).rgb;

    // Final color
    vec3 result = (ambient + diffuse + specular) * tex_color;
    frag_color = vec4(result, 1.0);
}
