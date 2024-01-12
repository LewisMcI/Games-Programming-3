#version 420 core
uniform sampler2D diffuse;
in vec2 tC;
out vec4 FragColor;

void main() {
	FragColor = texture(diffuse, tC);
	float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;                                                          
	FragColor = vec4(average, average, average, 1.0);
}