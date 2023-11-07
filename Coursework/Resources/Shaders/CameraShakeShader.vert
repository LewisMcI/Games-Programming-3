#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 tC;

uniform float random;

void main()
{
    gl_Position = vec4(aPos.x + (sin(random)/20), aPos.y + (cos(random)/20), 0.0, 1.0); 
    tC = aTexCoords;
}  