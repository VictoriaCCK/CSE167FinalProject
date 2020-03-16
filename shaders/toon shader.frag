#version 330 core
layout(location = 0) out vec4 fragColor;
// This is a sample fragment shader.

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
in vec3 output_normal;
in vec3 output_position;

uniform mat4 model;
uniform vec3 color;
uniform vec3 ambient;
uniform vec3 specular;
uniform vec3 diffuse;
uniform vec3 eye;

const int levels = 10;
const float scale_factor = 1/levels;
// You can output many things. The first vec4 type output determines the color of the fragment
//out vec4 fragColor;

void main()
{
    vec3 dl = vec3(10.0f, -3.f, 2.0f);
    vec3 lc = vec3(10.0f, 10.0f, 0.0f);
    vec3 L = normalize(dl - output_position);
    vec3 V = normalize(eye - output_position);
    
    float diffuse_color = max(0, dot(L, output_normal));
    vec3 diffuseColor = vec3(0.30, 0.80, 0.10);
    diffuseColor = diffuseColor * diffuse[0] * floor(diffuse_color * levels) * scale_factor;
    
    vec3 H = normalize(L + V);
    float specular_color = 0.0;
    
    if(dot(L, output_normal) > 0.0){
        specular_color = specular[0] * pow(max(0, dot(H, output_normal)), ambient[0]);
    }
    
    float specMask = (pow(dot(H, output_normal), ambient[0]) > 0.4) ? 1 : 0;
    float edgeDetection = (dot(V, output_normal) > 0.2) ? 1 : 0;
    vec3 color = edgeDetection * (color + diffuseColor + specular_color * specMask);
    fragColor = vec4(color, 1);
}



