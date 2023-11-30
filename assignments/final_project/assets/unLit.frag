#version 450

in vec2 UV;

out vec4 FragColor;

uniform sampler2D uSpriteSheet;

void main()
{
	FragColor = texture(uSpriteSheet, UV);
}