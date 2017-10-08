
uniform sampler2D picture;

varying vec2 textureCoordVarying;

out vec4 finalColor;

void main()
{
	finalColor = texture2D(picture, textureCoordVarying);
	return;

	// flowing code is to show shadow map
	float ans = texture2D(picture, textureCoordVarying).x;
	finalColor = vec4(1 - 100 * (1 - ans));
}