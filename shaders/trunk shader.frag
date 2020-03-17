#version 330 core
// This is a sample fragment shader.

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
in vec2 TexCoord;

out vec4 color;

// Texture samplers
uniform sampler2D outputTexture;

void main()
{
    // Linearly interpolate between both textures (second texture is only slightly combined)
    color = mix(texture(outputTexture, TexCoord), texture(outputTexture, TexCoord), 0.2);
}
