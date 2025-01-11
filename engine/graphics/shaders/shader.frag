#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D text;
uniform vec3 textColor;

void main()
{
    FragColor = texture(texture_diffuse1, TexCoord);
}
