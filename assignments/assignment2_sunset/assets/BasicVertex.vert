#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 DesiredColor;

uniform float uTime;
uniform vec3 uColor;
uniform float uBrightness;

void main()
{
	//VERTEX SHADERS MUST HAVE THE OUTPUT POSITION BE IN A VEC 4
	gl_Position = vec4(aPos.x, aPos.y + sin(uTime), aPos.z, 1.0);
	DesiredColor = vec4(uColor.xyz, uBrightness);
}