#version 330 core
out vec4 frag_color;

in vec3 frag_pos;
in vec3 normal;

struct Light {
    vec3 position;   // for point and spotlights
    vec3 direction;  // for directional and spotlights
    vec3 color;
    float intensity;
    int type;        // 0 = directional, 1 = point, 2 = spot
    float cut_off;   // fr spotlights
    float outer_cut_off; // for spotlights
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform vec3 view_pos;
uniform Material material;
uniform Light lights[10]; // max of 10 lights
uniform int num_lights;

vec3 calculate_directional_light(Light light, vec3 normal, vec3 view_dir);
vec3 calculate_point_light(Light light, vec3 normal, vec3 frag_pos, vec3 view_dir);
vec3 calculate_spot_light(Light light, vec3 normal, vec3 frag_pos, vec3 view_dir);

void main() {
    vec3 norm = normalize(normal);

    vec3 view_dir = normalize(view_pos - frag_pos);

    vec3 result = vec3(0.0);

    for (int i = 0; i < num_lights; i++) {
        if (lights[i].type == 0) { // directional light
            result += calculate_directional_light(lights[i], norm, view_dir);
        } else if (lights[i].type == 1) { // point light
            result += calculate_point_light(lights[i], norm, frag_pos, view_dir);
        } else if (lights[i].type == 2) { // spotlight
            result += calculate_spot_light(lights[i], norm, frag_pos, view_dir);
        }
    }

    frag_color = vec4(result, 1.0);
}

vec3 calculate_directional_light(Light light, vec3 normal, vec3 view_dir) {
    // light direction (for directional light)
    vec3 light_dir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, light_dir), 0.0);
    vec3 diffuse = light.color * diff * material.diffuse * light.intensity;

    // specular shading
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 specular = light.color * spec * material.specular * light.intensity;

    // results
    return (diffuse + specular);
}

vec3 calculate_point_light(Light light, vec3 normal, vec3 frag_pos, vec3 view_dir) {
    // light direction
    vec3 light_dir = normalize(light.position - frag_pos);

    // diffuse shading
    float diff = max(dot(normal, light_dir), 0.0);
    vec3 diffuse = light.color * diff * material.diffuse * light.intensity;

    // specular shading
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 specular = light.color * spec * material.specular * light.intensity;

    // attenuation (for point light)
    float distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * (distance * distance));

    // results
    return (diffuse + specular) * attenuation;
}

vec3 calculate_spot_light(Light light, vec3 normal, vec3 frag_pos, vec3 view_dir) {
    // light direction
    vec3 light_dir = normalize(light.position - frag_pos);

    // diffuse shading
    float diff = max(dot(normal, light_dir), 0.0);
    vec3 diffuse = light.color * diff * material.diffuse * light.intensity;

    // specular shading
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 specular = light.color * spec * material.specular * light.intensity;

    // spotlight intensity
    float theta = dot(light_dir, normalize(-light.direction));
    float epsilon = light.cut_off - light.outer_cut_off;
    float intensity = clamp((theta - light.outer_cut_off) / epsilon, 0.0, 1.0);

    // attenuation (for spotlight)
    float distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * (distance * distance));

    // results
    return (diffuse + specular) * attenuation * intensity;
}