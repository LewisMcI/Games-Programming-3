#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 TextureCoords;
layout (location = 2) in vec3 VertexNormal;
uniform mat4 transform;
out VS_OUT {
    vec2 texCoords;
} vertexDataOut;

void main()
{
	gl_Position =  transform * vec4(VertexPosition, 1.0);
	vertexDataOut.texCoords = TextureCoords;
}