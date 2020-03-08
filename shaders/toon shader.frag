#version 330 core
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

// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 fragColor;

void main()
{
    vec3 world_point;
    world_point = vec3(model * vec4(output_position, 1.0));
    vec3 world_normal;
    world_normal = transpose(inverse(mat3(model))) * output_normal;
    
    vec3 dl = vec3(0.0f, 50.0f, 0.0f);
    vec3 lc = vec3(1.0f, 1.0f, 0.0f);
    
    float c;
    vec3 R;
    vec3 L = normalize(dl - world_point);
    vec3 N;
    N = normalize(world_normal);
    c = dot(L, N);
    R = 2*dot(L, N)*N - L;
    
    vec3 e;
    e = normalize(eye - world_point);
    
    vec3 output_color;
    vec3 diffuseColor;
    vec3 specularColor;
    for (int i=0; i<3; i++) {
        diffuseColor[i] = lc[i]*max(c, 0)*diffuse[i];
        specularColor[i] = lc[i]*specular[i]*pow(max(dot(R, e), 0),4);
        output_color[i] = lc[i]*max(c, 0)*diffuse[i] + lc[i]*specular[i]*pow(max(dot(R, e), 0),4) + lc[i]*ambient[i];
    }
    
    float NdotL = max(dot(N, L), 0);
    float NdotV = max(dot(N, e), 0);
    
    if (NdotL < 0.5) {
        output_color = vec3(1.0, 0.5, 0.0);
    }else{
        if (NdotL >= 0.5 && NdotL<0.75) {
            output_color = diffuseColor;
        }else {
            output_color = specularColor;
        }
    }
    if (NdotV < 0.2) {
        output_color = vec3(0.0, 0.0, 0.0);
    }
    // Use the color passed in. An alpha of 1.0f means it is not transparent.
    fragColor = vec4(output_color, 1.0f);
}
