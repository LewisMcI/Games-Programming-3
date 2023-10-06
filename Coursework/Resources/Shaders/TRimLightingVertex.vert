#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 2) in vec3 VertexNormal;

uniform mat4 modelMatrix;
uniform mat4 transform;

out vec3 viewDirection;
out vec3 normal;

uniform vec3 camPos;

void main()
{
	vec4 worldPosition = transform * vec4(VertexPosition, 1.0);
	vec4 viewPosition = vec4(worldPosition.xyz - camPos, 1.0);
    gl_Position = transform * vec4(VertexPosition, 1.0);

	normal = mat3(transpose(inverse(modelMatrix))) * VertexNormal;

    viewDirection = -vec3(viewPosition);
}