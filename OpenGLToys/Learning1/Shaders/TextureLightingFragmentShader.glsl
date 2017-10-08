
uniform vec3 lightPosition;
uniform vec3 lightIntensities; // color of the Light
uniform mat4 model;
uniform sampler2D picture;

varying vec3 positionVarying;
varying vec2 textureCoordVarying;
varying vec3 normalVarying;

out vec4 finalColor;

void main()
{
    // calculate normal in world coordinates

    // normal matrix should get rid of translating and scaling, 
    // should mat3 first, get rid of translate,
    // and then inverse and transpose to get rid of scaling, I don't konw why
    mat3 normalMatrix = mat3(model);// transpose(inverse(mat3(model)));
    vec3 normal = normalize(normalMatrix * normalVarying);

    // position of pixel in world coordinates
    vec3 fragPosition = vec3(model * vec4(positionVarying, 1));

    // position to light vector
    vec3 surfaceToLight = lightPosition - fragPosition;

    // brightness is the angle of normal and surfaceToLight
    float brightness = dot(normal, surfaceToLight) / (length(normal) * length(surfaceToLight));
    
    // brightness *= 3;
    brightness = clamp(brightness, 0, 100);

    vec4 textureColor = texture2D(picture, textureCoordVarying);

    if (brightness < 0.1)
    {
        brightness = 0.1;
        finalColor = vec4(brightness * lightIntensities * textureColor.rgb, 1);
    }
    else
    {
        finalColor = vec4(brightness * lightIntensities * textureColor.rgb, 1);

    }

    if (textureColor.r < 0.5)
    {
        finalColor = vec4(0.1, 0, 0, 1);
     //   return;
    } 
    else
    {
        finalColor = vec4(1, 0, 0, 1);
       // return;
    }

    float r = textureColor.r;
    finalColor =  vec4(1.0 - 100 * (1 - r)); 
    //finalColor = vec4(1, 0, 1, 1);
}
    