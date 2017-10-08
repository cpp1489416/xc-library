
in vec3 position;
in vec3 color;
in vec3 normal;

varying vec3 positionVarying;
varying vec3 colorVarying;
varying vec3 normalVarying;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	positionVarying = position;
	colorVarying = color;
	normalVarying = normal;
	gl_Position = projection * view * model * vec4(position, 1);
}
