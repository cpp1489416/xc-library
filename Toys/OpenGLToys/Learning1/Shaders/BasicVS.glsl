in vec3 position;
in vec3 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

varying vec3 colorVarying;

void main()
{
	colorVarying = color;
	gl_Position = projection * view * model * vec4(position, 1);
}
