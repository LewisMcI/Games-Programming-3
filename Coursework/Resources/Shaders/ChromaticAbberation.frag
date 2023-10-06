
#version 420 core
uniform sampler2D diffuse;

in vec2 tC;

// Chromatic aberration offset values
uniform float RED_OFFSET;
uniform float GREEN_OFFSET;
uniform float BLUE_OFFSET;

layout(location = 0) out vec4 diffuseColor;

vec4 CalculateChromaticAbberation(){

    vec4 red = texture2D(diffuse, tC - RED_OFFSET);
    
    vec4 green = texture2D(diffuse, tC + GREEN_OFFSET);

    vec4 blue = texture2D(diffuse, tC + BLUE_OFFSET);
   
    return vec4(red.r, green.g, blue.b, 1.0);
}

void main() {
    diffuseColor = CalculateChromaticAbberation();
}