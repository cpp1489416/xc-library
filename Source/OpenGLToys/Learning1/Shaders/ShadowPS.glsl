
uniform sampler2D shadowMap;
uniform vec3 lightPosition;

varying vec4 lightFinalPositionVarying;
varying vec3 positionVarying;
varying vec3 normalVarying;
varying vec3 colorVarying;

out vec4 finalColor;

bool IsVisiable();

void main()
{
	if (!IsVisiable())
	{
		finalColor = vec4(0.0 * colorVarying, 1);
	}
	else
	{
		vec3 surfaceToLight = lightPosition - positionVarying;
		float brightness = dot(normalVarying, surfaceToLight) / (length(normalVarying) * length(surfaceToLight));
		brightness = clamp(brightness, 0.0, 1);
		finalColor = vec4(brightness * colorVarying, 1);
	}
}

bool IsVisiable()
{
	vec3 projCoords = lightFinalPositionVarying.xyz / lightFinalPositionVarying.w;
	vec2 uvCoords;
	uvCoords.x = 0.5 * projCoords.x + 0.5;
	uvCoords.y = 0.5 * projCoords.y + 0.5;
	float z = 0.5 * projCoords.z + 0.5;

	float mapDepth = texture(shadowMap, uvCoords).x;
	if (mapDepth < z)
	{
		return false;
	}
	else 
	{
		return true;
	}
}	
