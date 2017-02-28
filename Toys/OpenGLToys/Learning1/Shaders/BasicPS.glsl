#version 330 core

in vec3 colorVarying;

out vec4 finalColor;

void main()
{
    finalColor = vec4(colorVarying, 1);
}