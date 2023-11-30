#version 450

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNorm;
layout(location = 2) in vec2 vUV;

uniform mat4 _Model;
uniform mat4 _View;
uniform mat4 _OrthoProjection;

out vec2 UV;

void main()
{
	gl_Position =  _OrthoProjection * _View * _Model * vec4(vPos,1.0);

	UV = vUV;
}