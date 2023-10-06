#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 TextCoords;
layout (location = 2) in vec3 VertexNormal;

uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

// Toon
uniform mat4 transform;
uniform vec3 camPos;

out vec3 fNormal;
out vec3 fPosition;
out vec2 tC;
out vec3 viewDirection;

void main()
{
    fNormal = normalize(normalMatrix * VertexNormal);
    vec4 pos = modelViewMatrix * vec4(VertexPosition, 1.0);
    fPosition = pos.xyz;
    tC = TextCoords;
    gl_Position = projectionMatrix * pos;
    vec4 worldPosition = transform * vec4(VertexPosition, 1.0);
    vec4 viewPosition = vec4(worldPosition.xyz - camPos, 1.0);
    viewDirection = vec3(-viewPosition);
}