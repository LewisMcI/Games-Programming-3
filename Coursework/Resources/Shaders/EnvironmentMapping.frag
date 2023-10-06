#version 420 core

in VS_OUT{
    vec2 tC;
    vec3 Normal;
    vec3 Position;
} fs_in;

uniform vec3 camPos;
uniform samplerCube skybox;
uniform float reflectiveness;
layout (binding = 1) uniform sampler2D diffuse;

out vec4 FragColour;
void main()
{
	vec3 I = normalize(fs_in.Position - camPos); //vector to camera
	vec3 R = reflect(I, normalize(fs_in.Normal)); //calculate the reflection direction for the incident vector
	vec4 Colour = vec4(texture(skybox, R).rgb, 1.0);
	
	
	
	vec4 textureColour = texture2D(diffuse, fs_in.tC);
	FragColour = mix(textureColour, Colour, reflectiveness);
}