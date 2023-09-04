#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 DesiredColor;

uniform float uTime;

void main()
{
	//VERTEX SHADERS MUST HAVE THE OUTPUT POSITION BE IN A VEC 4
	gl_Position = vec4(aPos.x, aPos.y + sin(uTime), aPos.z, 1.0);
	DesiredColor = aColor;
}