#version 450 core

in vec3 DesiredColor;

out vec4 FragColor;

uniform float uTime;

void main()
{
	FragColor = vec4(DesiredColor* abs(sin(uTime)), 1.0);
}