
in vec3 position;
in vec2 textureCoord;
in vec3 normal;

varying vec3 positionVarying;
varying vec2 textureCoordVarying;
varying vec3 normalVarying;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    positionVarying = position;
    textureCoordVarying = textureCoord;
    normalVarying = normal;
    gl_Position = projection * view * model * vec4(position, 1);
}
