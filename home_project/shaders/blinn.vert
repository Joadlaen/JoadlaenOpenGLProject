// Blinn-Phong and Phong shared vertex shader
#version 410

in layout(location=0) vec3 aPos;
in layout(location=1) vec3 aNormal;

// M V P matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


out vec3 normal;
out vec3 fragPos;


void main()
{
    // homogeneous coordinate
    gl_Position = projection * modelview * vec4(pos, 1.0); 
    colour_vert = colour_in;
}