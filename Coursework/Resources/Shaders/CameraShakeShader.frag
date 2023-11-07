#version 420 core
uniform sampler2D diffuse;
in vec2 tC;
out vec4 FragColor;

void main() {
	FragColor = texture(diffuse, tC);
}