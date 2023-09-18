#version 450 core

in vec2 UV;

uniform float uTime;

uniform vec3 uSunColorMax;
uniform vec3 uSunColorMin;
uniform float uSunRadius;
uniform float uSunSpeed;

uniform vec3 uDayColorTop;
uniform vec3 uDayColorBottom;
uniform vec3 uNightColorTop;
uniform vec3 uNightColorBottom;

uniform vec3 uForegroundColor;

out vec4 FragColor;

float circleSDF(vec2 p, float r)
{
    return length(p) - r;
}

void main()
{
	//Need to fix the UV coords so the sun is offset properly
	vec2 normalizedUV = UV / (1080/720);

	vec2 adjustedUV = UV;
	adjustedUV.x *= (1080 / 720);

	float sunSpeed = uTime * uSunSpeed;

	vec2 sunPos = vec2(cos(sunSpeed)*1.5, sin(sunSpeed)-0.75);

	//Noramlized Sun Pos
	float normSunYPos = (sunPos.y / 2.0) + 0.75;

	float sunShape = circleSDF(UV - sunPos, uSunRadius);
	sunShape = smoothstep(-0.08, 0.08, sunShape);

	//Layering Colors
	vec4 sunColor = vec4(mix(uSunColorMin, uSunColorMax, normSunYPos), 1.0);

	vec3 dayColor = mix(uDayColorTop, uDayColorBottom, normalizedUV.y);
	vec3 nightColor = mix(uNightColorTop, uNightColorBottom, normalizedUV.y);
	vec3 background = mix(nightColor, dayColor, normSunYPos);

	vec3 sunset = mix(sunColor.rgb, background, sunShape * sunColor.a);

	//Mix in rollnig hills
	float hillStep = 0.15 + ( sin(normalizedUV.x * 2.56 + uTime) + sin(uTime) ) * 0.05;
	hillStep = 1.0 - step(hillStep, normalizedUV.y);

	vec3 finalColor = mix(sunset, uForegroundColor, hillStep);

	FragColor = vec4(finalColor, 1.0);
}

