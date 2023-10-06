#version 420 core
uniform sampler2D diffuse;
uniform int blurFactor;
in vec2 tC;

vec4 CalculateKuwaharaFilter(){
    // Kernel Size
    int kuwaharaKernel = blurFactor;

    // Returns image if blur not enabled
    if (kuwaharaKernel <= 0) 
    { 
        return texture2D(diffuse, tC);
    }
    // Init
    vec2 texSize = textureSize(diffuse, 0);

    // Keeping Track of values
    vec4 avgColours[4] = vec4[4]
    (
        vec4(0.0), // Bottom Left
        vec4(0.0), // Bottom Right
        vec4(0.0), // Top Left
        vec4(0.0)  // Top Right
    );

    float counters[4] = float[4]
    (
        0, // Bottom Left
        0, // Bottom Right
        0, // Top Left
        0  // Top Right
    );
    
    for(int i = -kuwaharaKernel; i < kuwaharaKernel; i++)
    {
        for (int j = -kuwaharaKernel; j < kuwaharaKernel; j++)
        {
            vec2 offset = vec2(i,j) / texSize;
            vec2 newtC = tC + offset;
            // Either bottom left or bottom right
            if (j < 0)
            {
                if (i < 0)
                {
                    avgColours[0] += texture2D(diffuse, newtC);
                    counters[0]++;
                    // Bottom Left
                }
                else if (i > 0)
                {
                    avgColours[1] += texture2D(diffuse, newtC);
                    counters[1]++;
                    //  Bottom Right
                }
                else
                {
                    avgColours[0] += texture2D(diffuse, newtC);
                    counters[0]++;

                    avgColours[1] += texture2D(diffuse, newtC);
                    counters[1]++;
                    // Both left + right
                }
            }
            else if (j > 0)
            {
                if (i < 0)
                {
                    avgColours[2] += texture2D(diffuse, newtC);
                    counters[2]++;
                    // Top Left
                }
                else if (i > 0)
                {
                    avgColours[3] += texture2D(diffuse, newtC);
                    counters[3]++;
                    //  Top Right
                }
                else
                {
                    avgColours[2] += texture2D(diffuse, newtC);
                    counters[2]++;

                    avgColours[3] += texture2D(diffuse, newtC);
                    counters[3]++;
                    // Both Top Left + Top Right
                }
            }
            else 
            {
                avgColours[0] += texture2D(diffuse, newtC);
                counters[0]++;

                avgColours[1] += texture2D(diffuse, newtC);
                counters[1]++;

                avgColours[2] += texture2D(diffuse, newtC);
                counters[2]++;

                avgColours[3] += texture2D(diffuse, newtC);
                counters[3]++;
                // All
            }
        }
    }

    // Averages
    avgColours[0] /= counters[0];
    avgColours[1] /= counters[1];
    avgColours[2] /= counters[2];
    avgColours[3] /= counters[3];

    // Standard Deviations
    float stds[4] = float[4]
    (
        0, // Bottom Left
        0, // Bottom Right
        0, // Top Left
        0  // Top Right
    );
    for(int i = -kuwaharaKernel; i < kuwaharaKernel; i++)
    {
        for (int j = -kuwaharaKernel; j < kuwaharaKernel; j++)
        {
            vec2 offset = vec2(i,j) / texSize;
            vec2 newtC = tC + offset;
            vec4 currentColour = texture2D(diffuse, newtC);
            float colour = dot(currentColour, currentColour);
            // Either bottom left or bottom right
            if (j < 0)
            {
                if (i < 0)
                {
                    stds[0] += pow(colour - dot(avgColours[0], avgColours[0]), 2.0);
                    // Bottom Left
                }
                else if (i > 0)
                {
                    stds[1] += pow(colour - dot(avgColours[1], avgColours[1]), 2.0);
                    //  Bottom Right
                }
                else
                {
                    stds[0] += pow(colour - dot(avgColours[0], avgColours[0]), 2.0);
                    stds[1] += pow(colour - dot(avgColours[1], avgColours[1]), 2.0);
                    // Both left + right
                }
            }
            else if (j > 0)
            {
                if (i < 0)
                {
                    stds[2] += pow(colour - dot(avgColours[2], avgColours[2]), 2.0);
                    // Top Left
                }
                else if (i > 0)
                {
                    stds[3] += pow(colour - dot(avgColours[3], avgColours[3]), 2.0);
                    //  Top Right
                }
                else
                {
                    stds[2] += pow(colour - dot(avgColours[2], avgColours[2]), 2.0);
                    stds[3] += pow(colour - dot(avgColours[3], avgColours[3]), 2.0);
                    // Both Top Left + Top Right
                }
            }
            else 
            {
                stds[0] += pow(colour - dot(avgColours[0], avgColours[0]), 2.0);
                stds[1] += pow(colour - dot(avgColours[1], avgColours[1]), 2.0);
                stds[2] += pow(colour - dot(avgColours[2], avgColours[2]), 2.0);
                stds[3] += pow(colour - dot(avgColours[3], avgColours[3]), 2.0);
                // All
            }
        }
    }
    // Standard Deviations
    stds[0] /= counters[0];
    stds[1] /= counters[1];
    stds[2] /= counters[2];
    stds[3] /= counters[3];

    // Find Minimum Standard Deviation and Set Colour to Lowest
    int minimumStd = 0;
    for (int i = 1; i <= 3; i++)
    {
        if (stds[i] < stds[minimumStd])
        {
            minimumStd = i;
        }
    }
    
    return avgColours[minimumStd];
}

layout(location = 0) out vec4 diffuseColor;

void main() {
    diffuseColor = CalculateKuwaharaFilter();
}