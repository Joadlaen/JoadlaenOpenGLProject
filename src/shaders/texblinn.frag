#version 410

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D textureMap;
uniform bool hasTexture;

out vec4 colour_out;

void main()
{
    vec3 colour = hasTexture
        ? texture(textureMap, texCoord).rgb
        : vec3(1.0);

    vec3 ambient = 0.05 * colour;

    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 norm = normalize(normal);
    float diff = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = diff * colour;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(0.3) * spec;

    colour_out = vec4(ambient + diffuse + specular, 1.0);
}
