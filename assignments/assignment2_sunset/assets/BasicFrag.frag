#version 450 core

in vec4 DesiredColor;

out vec4 FragColor;

uniform float uTime;

void main()
{
	FragColor = DesiredColor;
}