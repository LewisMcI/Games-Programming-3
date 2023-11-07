#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 TextCoords;


out vec2 tC;

void main()
{
	gl_Position = vec4(VertexPosition, 1.0f);
	tC = TextCoords;
}