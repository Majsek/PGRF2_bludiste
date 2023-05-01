#version 450 core

// Outputs colors in RGBA
out vec4 FragColor;

// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

// Gets the Texture Unit from the main function
layout (binding = 0) uniform sampler2D tex0;

// Imports from the main function
uniform float random;
uniform float fogRange;

in float depth;

void main()
{
    float fog_factor = 1-exp(-pow(depth,fogRange)) * random;

    FragColor =
    mix(
    texture(tex0, texCoord),
    vec4(0,0,0,0),
    clamp(fog_factor,0,1)
    );
}

