#version 450 core

in vec4 DesiredColor;

out vec4 FragColor;

uniform float uTime;

uniform vec3 uSunColor;
uniform float uSunRadius;
uniform float uSunSpeed;

uniform vec3 uDayColorTop;
uniform vec3 uDayColorBottom;
uniform vec3 uNightColorTop;
uniform vec3 uNightColorBottom;

uniform vec3 uForegroundColor;

void main()
{
	FragColor = DesiredColor;

	/*
	// Normalized pixel coordinates (from 0 to 1)
    vec2 normUV = fragCoord/iResolution.xy;
    
    //-1 to 1
    vec2 adjustedUV = normUV*2.0 - 1.0;
    //Correct for aspect ratio
    adjustedUV.x *= iResolution.x / iResolution.y;

    //float t = sin(uv.x * 6.28 + iTime) * 0.5 + 0.5;
    //float t = floor(uv.x*4.0);
    //float t = fract(uv.x*5.0);
    //float t = mod(uv.x*6.0, 2.0);
    //float t = mod(floor(uv.x*8.0), 2.0);
    
    //Checker board
    //uv = floor(uv * 8.0);
    //float t = mod(uv.x+uv.y,2.0);

    //Abs
    //float t = abs( mod(uv.x*4.0 + iTime, 2.0) - 1.0 );
    
    //Step
    //float t = step(0.25, uv.x);
    
    //Rolling hills
    //float t = 0.5 + sin(uv.x )*0.5;
    //t = step(t, uv.y);
    
    //Inverse Lerp - smooth step
    //float edge = sin(iTime)*0.5+0.5;
    //float t = smoothstep(edge-0.05, edge+0.05, uv.y);
    
    //Length + Distance
    //float t = length(uv);
    //float t = distance (uv, vec2(0.5));
    
    //Circle SDF
    //vec2 circleAPos = vec2(cos(iTime)*1.5, (sin(iTime)-1.0) );
    //float circleRadius = 0.25;
    
    //float d = circleSDF(uv-circleAPos, circleRadius);
    
    //Stepped SDF
    
    //Hard Circle
    //d = step (0.0, d);
    
    //Soft Circle
    //d = smoothstep(0.0, 0.20, d);
    
    //Lerp AKA mix() in glsl
    //vec3 colA = vec3(1.0, 0.0, 0.0);
    //vec3 colB = vec3(0.0, 0.0, 1.0);
    //vec3 col = mix(colA, colB, uv.x);
    
    float sunSpeed = iTime * 0.85;
    
    //Sun  
    vec2 sunPos = vec2(cos(sunSpeed)*1.5, (sin(sunSpeed)-0.75) );
    
    //0 -> 1 sun pos
    float normSunYPos = (sunPos.y / 2.0) + 0.75;
     
    float sunRadius = 0.35;
    
    float sunShape = circleSDF(adjustedUV-sunPos, sunRadius);
    
    sunShape = smoothstep(-0.08, 0.08, sunShape);
    
    //Layering colors
    vec4 sunColorMax = vec4(0.89, 0.53, 0.03, 1.0);
    vec4 sunColorMin = vec4(0.72, 0.32, 0.15, 1.0);
    
    vec4 sunColor = mix(sunColorMin, sunColorMax, normSunYPos);
    
    vec3 dayColorTop = vec3(0.875, 0.25, 0.09);
    vec3 dayColorBottom = vec3(0.45, 0.25, 0.42);
    
    vec3 dayColor = mix(dayColorTop, dayColorBottom, normUV.y);
    
    vec3 nightColorTop = vec3(0.875, 0.33, 0.40);
    vec3 nightColorBottom = vec3(0.16, 0.125, 0.39);
    
    vec3 nightColor = mix(nightColorTop, nightColorBottom, normUV.y);
    
    vec3 background = mix(nightColor, dayColor, normSunYPos);
    
    vec3 sunset = mix(sunColor.rgb, background, sunShape * sunColor.a);
    
    //Mix in rolling hills
    float hillStep = 0.15 + ( sin(normUV.x*2.56 +iTime) + sin(iTime) ) * 0.05;
    hillStep = 1.0 - step(hillStep, normUV.y);
    
    vec3 hillColor = vec3(0.14, 0.05, 0.01);
    
    vec3 final = mix(sunset, hillColor, hillStep);
    
    // Output to screen
    fragColor = vec4(final, 1.0);

    float circleSDF(vec2 p, float r)
{
    return length(p) - r;
}
	*/
}