#version 450 core

in vec2 UV;

uniform float uTime;
uniform vec2 uScreenSize;

uniform sampler2D uBackgroundTexture;
uniform sampler2D uNoiseTexture;

out vec4 FragColor;

void main()
{
	float noise = texture(uNoiseTexture, UV).r;

	//Only want noise applied to the bottom half of the background
	float applyNoise = step(0.45, UV.y) - 1;

	vec2 adjustedUV = UV + ( (noise * applyNoise) * 0.01f );

	vec4 bg = texture(uBackgroundTexture, vec2(adjustedUV.x + (uTime*0.25), adjustedUV.y));

	//vec4 noise = texture(uNoiseTexture, UV);

	//vec4 final = mix(bg, noise, noise.a * 0.2);

	FragColor = bg;
}

