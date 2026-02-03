// Blinn-Phong and Phong shared vertex shader
#version 410

in layout(location=0) vec3 aPos;
in layout(location=1) vec3 aNormal;
in layout(location=2) vec2 aTexCoord;

// M V P matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// out vec3 colour_vert;
out vec3 normal;
out vec3 fragPos;
out vec2 texCoord;

void main()
{
    // homogeneous coordinate
    gl_Position = projection * view * model * vec4(aPos, 1.0); 
    
    fragPos = vec3(model * vec4(aPos, 1.0));

mat3 normalMatrix = transpose(inverse(mat3(model)));
normal = normalize(normalMatrix * aNormal);


    texCoord = aTexCoord;
}