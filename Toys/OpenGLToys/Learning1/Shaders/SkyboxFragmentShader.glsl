
varying vec2 textureCoordVarying;
uniform sampler2D skybox;
out vec4 color;

void main()
{
	color = texture2D(skybox, textureCoordVarying);
}