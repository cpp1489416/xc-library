
uniform vec3 lightPosition;
uniform vec3 lightIntensities; // color of the Light
uniform mat4 model;

varying vec3 positionVarying;
varying vec3 colorVarying;
varying vec3 normalVarying;

out vec4 finalColor;

void main()
{
    // calculate normal in world coordinates

    // normal matrix should get rid of translating, 
    mat3 normalMatrix = mat3(model);
    vec3 normal = normalize(normalMatrix * normalVarying);

    // position of pixel in world coordinates
    vec3 fragPosition = vec3(model * vec4(positionVarying, 1));

    // position to light vector
    vec3 surfaceToLight = lightPosition - fragPosition;

    // brightness is the angle of normal and surfaceToLight
    float brightness = dot(normal, surfaceToLight) / (length(normal) * length(surfaceToLight));
    brightness = clamp(brightness, 0, 1)  ;

    if (brightness < 0.20)
    {
        brightness = 0.2;
        finalColor = vec4(brightness * lightIntensities * colorVarying.rgb, 1);
    }
    else
    {
        finalColor = vec4(brightness * lightIntensities * colorVarying.rgb, 1);
    }

    // finalColor = vec4(lightPosition, 1);
     //finalColor =  vec4(lightIntensities, 1); 
    // finalColor = vec4(1, 0, 1, 1);
}
    