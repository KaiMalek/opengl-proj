#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
    vec4 color = texture(text, TexCoords);
    if (color.r < 0.1)
        discard;

    FragColor = vec4(textColor, 1.0) * color;
}
