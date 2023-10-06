#version 400

in vec3 normal;
in vec3 viewDirection;

out vec4 FragColour;


uniform vec3 rimColor;
uniform float rimPower;
uniform vec3 lightDir;

vec4 CalculateToonColour();
vec4 CalculateRimColour();

void main()
{
	//FragColour = CalculateRimColour() * (CalculateToonColour() * 0);
    FragColour = mix(CalculateToonColour(), CalculateRimColour(), 0.5f);
}

vec4 CalculateRimColour()
{
    float rim = dot(normalize(normal), normalize(viewDirection));
    rim = 1.0 - rim;
    rim = max(0.0, rim);
    rim = pow(rim, rimPower);

    rim = smoothstep(0.3, 0.4, rim);

    return vec4(rimColor, 1.0) * rim;
}

vec4 CalculateToonColour()
{
	float intensity;
	vec4 colour;

	intensity = dot(lightDir, normal);

	if (intensity > .9)
		colour = vec4(1.0, 0, .5,1.0);
	else if (intensity > .8)
		colour = vec4(.8, .0, .5, 1.0);
	else if (intensity > .7)
		colour = vec4(.8, .0, .5, 1.0);
	else if (intensity > .6)
		colour = vec4(.6, .0, .5, 1.0);
	else if (intensity > .5)
		colour = vec4(.5, .0, .5, 1.0);
	else if (intensity > .4)
		colour = vec4(.4, .0, .5, 1.0);
	else if (intensity > .3)
		colour = vec4(.3, .0, .5, 1.0);
	else if (intensity > .2)
		colour = vec4(.2, .0, .5, 1.0);
	else
		colour = vec4(.1, .0, .5, 1.0);


	return colour;
}