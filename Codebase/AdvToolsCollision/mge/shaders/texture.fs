// //DIFFUSE TEXTURE FRAGMENT SHADER
// #version 330 // for glsl version (12 is for older versions , say opengl 2.1

// uniform sampler2D diffuseTexture;
// in vec2 texCoord;
// out vec4 fragment_color;

// void main( void ) {
// 	fragment_color = texture(diffuseTexture,texCoord);
// }
//DIFFUSE TEXTURE FRAGMENT SHADER
#version 400


struct Light {

    float ambientIntensity;
    vec3 lightColor;
    vec3 lightPos;
};

uniform Light lights[10];
uniform int lightCount;

in vec3 nor;
varying vec3 worldPos;

uniform vec3 camPos;

uniform sampler2D diffuseTexture;
uniform sampler2D splatTexture1;
uniform sampler2D splatTexture2;
uniform sampler2D splatTexture3;
uniform sampler2D splatTexture4;
in vec2 texCoord;


out vec4 fragment_color;

void main( void ) {

    if (true) // if using normal map things
    {
        fragment_color = texture(diffuseTexture,texCoord);
    }
    else
    {
    
        vec3 fragColor = vec3(0,0,0);

        vec4 splatmapColor = texture(diffuseTexture,texCoord);

        vec3 diff1 = vec3(texture(splatTexture1,texCoord));
        vec3 diff2 = vec3(texture(splatTexture2,texCoord));
        vec3 diff3 = vec3(texture(splatTexture3,texCoord));
        vec3 diff4 = vec3(texture(splatTexture4,texCoord));
        vec3 diffColor = splatmapColor.r * diff1 + 
                         splatmapColor.g * diff2 + 
                         splatmapColor.b * diff3 + 
                         splatmapColor.a * diff4;

        // For attenuation, no need to redeclare it in the for loop
        float c1 = 1;
        float c2 = 0.2f;
        float c3 = 0;

        // diffColor = vec3(texture(diffuseTexture,texCoord));

        for (int i = 0; i < lightCount; i++) {
        
        
            // Ambient
            vec3 aIntense = vec3(lights[i].ambientIntensity, lights[i].ambientIntensity, lights[i].ambientIntensity);
            vec3 ambient = aIntense * lights[i].lightColor * diffColor;
    
            // Diffuse
            vec3 lightDirection = lights[i].lightPos - worldPos;
            float dIntense = max(dot(normalize(lightDirection), nor), 0);
            vec3 diffuse = dIntense * lights[i].lightColor * diffColor;
        
            // Specular
            vec3 r = normalize(lightDirection - 2 * dot(lightDirection, nor) * nor);
            vec3 v = normalize(worldPos - camPos);
            int s = 500;
            float sIntense = pow(max(dot(r, v), 0), s);
            vec3 specular = sIntense * lights[i].lightColor * diffColor;

            // Attenuation
            float dist = distance(lights[i].lightPos, worldPos);
    
            vec3 aDiffuse = diffuse / (c1 + c2 * dist + c3 * dist * dist);
            vec3 aSpecular = specular / (c1 + c2 * dist + c3 * dist * dist);
        

            vec3 lightResult = ambient + aDiffuse + aSpecular;

            fragColor += lightResult;
        }

        fragment_color = vec4(fragColor,1);
    }
}
