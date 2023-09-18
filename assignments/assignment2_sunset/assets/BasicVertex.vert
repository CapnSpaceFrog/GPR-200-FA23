#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

uniform float uTime;

out vec2 UV;

void main()
{
	//VERTEX SHADERS MUST HAVE THE OUTPUT POSITION BE IN A VEC 4
	gl_Position = vec4(aPos, 1.0);
	UV = aUV;
}