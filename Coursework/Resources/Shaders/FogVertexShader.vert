#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 TextCoords;

uniform mat4 transform;

out vec4 v_pos; 
out vec2 tC;

void main()
{
	v_pos = transform * vec4(VertexPosition, 1.0);
	gl_Position = transform * vec4(VertexPosition, 1.0);
	
	tC = TextCoords;
}
