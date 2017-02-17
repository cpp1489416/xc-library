
in vec3 position;
in vec2 textureCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

varying vec2 textureCoordVarying;

void main()
{
	textureCoordVarying = textureCoord;
	gl_Position = projection * view * model * vec4(position, 1);
}