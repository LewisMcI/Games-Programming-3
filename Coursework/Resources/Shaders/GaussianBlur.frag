#version 420 core

uniform sampler2D diffuse;
uniform int blurFactor;
in vec2 tC;

const float PI = 3.1415926535;

/* Calculates Gaussian Weight at Position
*  It is assumed that the mean value (aka center position) is at 0,0
*  Found using the formula (1 / (standardDeviation * (sqrt(2 * pi))) * e^((-1/2) * ((x - mean) / standardDeviation) * ((y - mean) / standardDeviation)))
*  Where x and y are the current position.
*/
float CalculateGaussianWeight(vec2 currentPos, float sigma)
{
    return (1 / (2 * PI * (pow(sigma, 2.0)))) * exp(-((pow(currentPos.x, 2.0) + pow(currentPos.y, 2.0)) / (2 * pow(sigma, 2.0))));
}

vec4 CalculateGaussianBlur(){
    // Kernel Size
    int gaussianBlurKernel = blurFactor;

    // Returns image if blur not enabled
    if (gaussianBlurKernel <= 0) 
    { 
        return texture2D(diffuse, tC);
    }
    // Init
    vec4 weightedAverageColour = vec4(0.0);

    vec2 texSize = textureSize(diffuse, 0);
    
    float totalWeight = 0;
    // Creates a grid around the current fragment with a size of 2 * kernel size + 1.
    for (int i = -gaussianBlurKernel; i <= gaussianBlurKernel; i++) 
    {
        for (int j = -gaussianBlurKernel; j <= gaussianBlurKernel; j++) 
        {
            // Calculate Weight
            float weight = CalculateGaussianWeight(vec2(i,j), 0.5 * float(gaussianBlurKernel));
            totalWeight += weight;

            // Calculate current position.
            vec2 offset = vec2(i,j) / texSize;
            vec2 newtC = tC + offset;
            weightedAverageColour += texture2D(diffuse, newtC) * weight;
        }
    }
    /* Total weight is found since we have a boxBlurKernel by boxBlurKernel matrix.
    *  The matrix is run from its negative value to its positive and includes both sides.
    */
    weightedAverageColour /= totalWeight;
    return weightedAverageColour;
}

layout(location = 0) out vec4 diffuseColor;
void main() {
    // Gaussian filter
    diffuseColor = CalculateGaussianBlur();
}