#version 420 core

out VS_OUT
{
	vec3 tC;
} vs_out;

uniform mat4 view;

void main(void){
	vec3[4] vertices = vec3[4] (vec3(-1.0, -1.0, 1.0),
							vec3(1.0, -1.0, 1.0),
							vec3(-1.0, 1.0, 1.0),
							vec3(1.0, 1.0, 1.0));
	vs_out.tC = mat3(view) * vertices[gl_VertexID];
	gl_Position = vec4(vertices[gl_VertexID], 1.0f);
}