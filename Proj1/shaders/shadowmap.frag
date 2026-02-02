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

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    // transform to [0,1]
    projCoords = projCoords * 0.5 + 0.5;

    // outside the shadow map -> no shadow
    if (projCoords.x < 0.0 || projCoords.x > 1.0 ||
        projCoords.y < 0.0 || projCoords.y > 1.0 ||
        projCoords.z > 1.0)
    {
        return 0.0;
    }

    // depth from shadow map (closest surface to light)
    float closestDepth = texture(shadowMap, projCoords.xy).r;

    // current fragment depth
    float currentDepth = projCoords.z;

    // bias to prevent shadow acne
    float bias = 0.005;

    // shadow test
    return currentDepth - bias > closestDepth ? 1.0 : 0.0;
}


void main()
{   
    vec3 colour = vec3(1.0, 0.0, 0.0);
    if (hasTexture)
        colour = texture(textureMap, texCoord).rgb;
    
    /*
    vec3 normal = normalize(normal);
    vec3 lightColor = vec3(1.0);

    // ambient
    vec3 ambient = 0.15 * lightColor;
    // diffuse
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor; 
    */

    // 1. ambient
    vec3 ambient = 0.05 * colour;

    // 2. diffuse
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 norm = normalize(normal);
    float diff = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = diff * colour;
    
    // 3. specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    
    // the shininess coefficient beta = 32.0 
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);

    // assuming a light source with a bright white colour
    vec3 specular = vec3(0.3) * spec;   
    
    // calculate shadow using the light space position
    float shadow = ShadowCalculation(fragPosLightSpace);
    vec3 lighting = ambient + (1.0 - shadow) * (diffuse + specular);    
    
    colour_out = vec4(lighting, 1.0);
}