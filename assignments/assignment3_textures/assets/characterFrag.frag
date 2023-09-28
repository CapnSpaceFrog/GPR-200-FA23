#version 450 core

in vec2 UV;

uniform float uTime;
uniform vec2 uScreenSize;

uniform sampler2D uCharacterTexture;

out vec4 FragColor;

float circleSDF(vec2 p, float r)
{
    return length(p) - r;
}

void main()
{
	vec2 adjustedUV = (UV * 2) - 1.0;
	adjustedUV.x *= (uScreenSize.x / uScreenSize.y);

	vec4 color = texture(uCharacterTexture, UV);

	FragColor = color;
}

