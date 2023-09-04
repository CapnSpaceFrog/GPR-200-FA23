#version 450 core

in vec3 DesiredColor;

out vec4 FragColor;

void main()
{
	FragColor = vec4(DesiredColor, 1.0f);
}