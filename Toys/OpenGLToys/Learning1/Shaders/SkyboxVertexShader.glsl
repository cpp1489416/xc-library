
in vec3 position;
in vec2 textureCoord;

uniform mat4 projection;
uniform mat4 view; 

varying vec2 textureCoordVarying;

void main()
{
	textureCoordVarying = textureCoord;
	gl_Position = projection * view * vec4(position, 1.0);
}