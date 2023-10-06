#version 420 core

uniform sampler2D diffuse;
uniform int blurFactor = 5;
in vec2 tC;

layout(location = 0) out vec4 diffuseColor;

vec4 CalculateBoxBlur(){
    // Kernel Size
    int boxBlurKernel = blurFactor;
    // Returns image if blur not enabled
    if (boxBlurKernel <= 0) 
    { 
        return texture2D(diffuse, tC);
    }

    // Init
    vec4 averageColour = vec4(0.0);

    vec2 texSize = textureSize(diffuse, 0);


    // Creates a grid around the current fragment with a size of 2 * kernel size + 1.
    for (int i = -boxBlurKernel; i <= boxBlurKernel; i++) 
    {
        for (int j = -boxBlurKernel; j <= boxBlurKernel; j++) 
        {
            // Calculate current position.
            vec2 offset = vec2(i,j) / texSize;
            vec2 newtC = tC + offset;
            averageColour += texture2D(diffuse, newtC);
        }
    }
    /* Total weight is found since we have a boxBlurKernel by boxBlurKernel matrix.
    *  The matrix is run from its negative value to its positive and includes both sides.
    */
    float totalWeight = (2 * boxBlurKernel + 1) * (2 * boxBlurKernel + 1);
    averageColour /= totalWeight;
    return averageColour;
}

void main() { 
    diffuseColor = CalculateBoxBlur();
}