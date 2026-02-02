// shadowmap.frag
#version 410

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;
in vec4 fragPosLightSpace;

uniform bool hasTexture;
uniform sampler2D textureMap;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 colour_out;

// Calculate shadow with bias to prevent shadow acne
float ShadowCalculation(vec4 fragPosLightSpace, vec3 norm, vec3 lightDir)
{
    // Perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    // Depth from shadow map
    float closestDepth = texture(shadowMap, projCoords.xy).r;

    // Depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    // Bias to avoid self-shadowing
    float bias = max(0.05 * (1.0 - dot(norm, lightDir)), 0.005);

    // Shadow test
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    // Optional: prevent shadows outside light frustum
    if (projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}

void main()
{
    // Base color
    vec3 colour = vec3(1.0, 0.0, 0.0);
    if (hasTexture)
        colour = texture(textureMap, texCoord).rgb;

    // Normalize vectors
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    // Ambient
    vec3 ambient = 0.05 * colour;

    // Diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * colour;

    // Specular
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(0.3) * spec;

    // Calculate shadow
    float shadow = ShadowCalculation(fragPosLightSpace, norm, lightDir);

    // Combine lighting
    vec3 lighting = ambient + (1.0 - shadow) * (diffuse + specular);

    colour_out = vec4(lighting, 1.0);
}
