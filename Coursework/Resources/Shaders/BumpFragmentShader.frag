#version 400

in vec2 tC;

out vec4 FragColour;

uniform sampler2D normalT;
uniform sampler2D diffuse;

layout(location = 0) out vec4 diffuseColor;

void main()
{
	vec3 normal = texture2D(normalT, tC).rgb;
	normal = normalize(normal); // *2 -1

	vec3 colour = texture2D(diffuse, tC).rgb;

	vec3 ambient = 0.8 * colour;

	vec3 lightDir = vec3(0.5, 0.5, 1.0);
	float diffuseContr = max(dot(lightDir, normal), 0.0f);

	vec3 diffuse = diffuseContr * colour;

	diffuseColor = vec4(diffuse + ambient, 1.0f);
}