
in vec3 position;
in vec3 color;
in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightProjection;
uniform mat4 lightView;
uniform mat4 lightModel;
	
varying vec4 lightFinalPositionVarying;
varying vec3 positionVarying;
varying vec3 normalVarying;
varying vec3 colorVarying;

void main()
{
	lightFinalPositionVarying = lightProjection * lightView * lightModel * vec4(position, 1);
	colorVarying = color;
	normalVarying = (model * vec4(normal, 0)).xyz;
	positionVarying = (model * vec4(position, 1)).xyz;

	gl_Position = projection * view * model * vec4(position, 1);

}