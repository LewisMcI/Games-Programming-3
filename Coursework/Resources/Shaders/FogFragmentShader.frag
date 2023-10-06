#version 400

out vec4 FragColor;

in vec4 v_pos; 
in vec2 tC;
vec3 fogColor = vec3(0.46f, 0.57f, 0.71f);

uniform sampler2D diffuse;

float maxDist = 10.0f; //fog max distance
float minDist = 0.0f; //fog min distance

void main() 
{
	float dist = abs(v_pos.z);
	float fogFactor = (maxDist - dist) / (maxDist - minDist);
	fogFactor = clamp(fogFactor, 0.0, 1.0);
	vec3 lightColor = vec3(0.1,0.1,0.1);
	vec3 color = mix(fogColor, vec3(texture2D(diffuse, tC)), fogFactor);

	FragColor = vec4(color, 1.0);
}
