#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

uniform float uTime;

out vec2 UV;

void main()
{

	//May want to scale up background so noise doesn't cause any bleed
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

	UV = aUV;
}