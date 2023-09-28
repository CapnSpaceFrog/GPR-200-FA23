#version 450 core

in vec2 UV;

uniform float uTime;
uniform vec2 uScreenSize;

uniform sampler2D uBackgroundTexture;
uniform sampler2D uNoiseTexture;
uniform sampler2D uTilingTexture;

out vec4 FragColor;

void main()
{
	float noise = texture(uNoiseTexture, UV).r;

	//Only want noise applied to the bottom half of the background
	float applyNoise = step(0.45, UV.y) - 1;

	vec2 noiseUV = UV + noise * 0.1;
	vec4 tiling = texture(uTilingTexture, noiseUV * 25 + (uTime*0.25));

	vec2 steppedUV = UV + ( (noise * applyNoise) * 0.01 );
	vec4 bg = texture(uBackgroundTexture, vec2(steppedUV.x + (uTime*0.25), steppedUV.y));

	vec4 final = mix(bg, tiling, tiling.a * 0.2);

	FragColor = final;
}

