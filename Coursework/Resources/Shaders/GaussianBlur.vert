#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 TextCoords;

uniform mat4 transform;

out vec2 tC;

void main()
{
	gl_Position =  transform * vec4(VertexPosition, 1.0f);
	tC = TextCoords;
}