#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 TextCoords;
layout (location = 2) in vec3 VertexNormal;

uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

out vec3 fNormal;
out vec3 fPosition;
out vec2 tC;

void main()
{
  fNormal = normalize(normalMatrix * VertexNormal);
  vec4 pos = modelViewMatrix * vec4(VertexPosition, 1.0);
  fPosition = pos.xyz;
  tC = TextCoords;
  gl_Position = projectionMatrix * pos;
}