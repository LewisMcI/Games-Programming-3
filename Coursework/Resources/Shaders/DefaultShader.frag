#version 420

in vec2 texCoord0;
out vec4 fragColor;
uniform sampler2D diffuse;

void main()
{
    fragColor = texture(diffuse, texCoord0);
}