#version 450

struct Light
{
	vec3 pos;
	vec3 color;
};

in Surface
{
	vec2 UV;
	vec3 WorldPosition;
	vec3 WorldNormal;
} fs_in;

out vec4 FragColor;

uniform sampler2D _Texture;

uniform vec3 uCameraPos;

uniform float uAmbient;
uniform float uDiffuse;
uniform float uSpecular;
uniform float uShininess;

#define MAX_LIGHTS 4

uniform Light _Lights[MAX_LIGHTS];

void main()
{
	vec3 worldNormFixed = normalize(fs_in.WorldNormal);

	vec3 lightDir = normalize(_Lights[0].pos - fs_in.WorldPosition);

	//light calcs done here
	float diffuseIntensity = uDiffuse * max( dot(worldNormFixed, lightDir), 0 );

	vec3 reflectedWorldNorm = reflect(-lightDir, worldNormFixed);

	vec3 dirToCamera = normalize(uCameraPos - fs_in.WorldPosition);

	float specularIntensity = uSpecular * pow( max(dot(reflectedWorldNorm, dirToCamera), 0), uShininess );

	// texture(_Texture, fs_in.UV) * diffuseIntensity ) + 
	FragColor = vec4( ( texture(_Texture, fs_in.UV).rgb *  (_Lights[0].color * (diffuseIntensity + specularIntensity) ) ), 1) );
}