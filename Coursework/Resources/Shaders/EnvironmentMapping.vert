#version 440

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 TextCoords;
layout (location = 2) in vec3 aNormal;

out VS_OUT{
    vec2 tC;
    vec3 Normal;
    vec3 Position;
} vertexDataOut;

uniform mat4 model;
uniform mat4 transform;

void main()
{
    vertexDataOut.tC = TextCoords;
    vertexDataOut.Normal = mat3(transpose(inverse(model))) * aNormal;
    vertexDataOut.Position = vec3(model * vec4(aPos, 1.0));

    gl_Position = transform * vec4(aPos, 1.0);
}  
