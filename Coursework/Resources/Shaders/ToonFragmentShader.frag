#version 400

uniform vec3 lightDir;
in vec3 normal;

out vec4 FragColour;

void main()
{
	float intensity;
	vec4 color;

	intensity = dot(lightDir, normal);

	if (intensity > .9)
		color = vec4(1.0, 0, .5,1.0);
	else if (intensity > .8)
		color = vec4(.8, .0, .5, 1.0);
	else if (intensity > .7)
		color = vec4(.8, .0, .5, 1.0);
	else if (intensity > .6)
		color = vec4(.6, .0, .5, 1.0);
	else if (intensity > .5)
		color = vec4(.5, .0, .5, 1.0);
	else if (intensity > .4)
		color = vec4(.4, .0, .5, 1.0);
	else if (intensity > .3)
		color = vec4(.3, .0, .5, 1.0);
	else if (intensity > .2)
		color = vec4(.2, .0, .5, 1.0);
	else
		color = vec4(.1, .0, .5, 1.0);

	FragColour = color;
}