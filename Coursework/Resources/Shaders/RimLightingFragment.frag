#version 330

in vec3 normal;
in vec3 viewDirection;

out vec4 fragmentColor;

uniform vec3 rimColor;
uniform float rimPower;

uniform sampler2D diffuse;

void main()
{
    float rim = dot(normalize(normal), normalize(viewDirection));
    rim = 1.0 - rim;
    rim = max(0.0, rim);
    rim = pow(rim, rimPower);

    rim = smoothstep(0.3, 0.4, rim);
    fragmentColor = vec4(rimColor, 1.0) * rim;
}