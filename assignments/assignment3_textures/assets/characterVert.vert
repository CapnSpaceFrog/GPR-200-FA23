#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

uniform float uTime;
uniform float uCharacterScale;

out vec2 UV;

void main()
{
	//SCALE DOWN CHARACTER SIZE
	vec3 scaledPos = aPos * uCharacterScale;

	//SET CHARACTER POSITION
	gl_Position = vec4(scaledPos.x + (abs(sin(uTime*0.5)) - 0.5), scaledPos.y + ( abs(sin(uTime*0.5)) - 0.5), scaledPos.z, 1.0);

	//PASS ON UV CORDS
	UV = aUV;
}