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

uniform vec3 uAmbientLightColor;
uniform vec3 uCameraPos;

uniform float uAmbient;
uniform float uDiffuse;
uniform float uSpecular;
uniform float uShininess;

uniform int uActiveLights;

uniform bool uBlinnPhongSpec;

#define MAX_LIGHTS 4

uniform Light _Lights[MAX_LIGHTS];

void main()
{
	vec3 worldNormFixed = normalize(fs_in.WorldNormal);
	vec3 dirToCamera = normalize(uCameraPos - fs_in.WorldPosition);

	vec3 accumulatedLightColor;
	for (int i = 0; i < uActiveLights; i++)
	{
		vec3 lightDir = normalize(_Lights[i].pos - fs_in.WorldPosition);

		//DIFFUSE LIGHT
		float diffuseIntensity = uDiffuse * max( dot(worldNormFixed, lightDir), 0 );
		vec3 diffuseLight = _Lights[i].color * diffuseIntensity;

		//SPECULAR LIGHT
		float specularIntensity;

		if (uBlinnPhongSpec)
		{
			vec3 halfVector = normalize( (lightDir + dirToCamera) );

			specularIntensity = uSpecular * pow( max(dot(halfVector, worldNormFixed), 0), uShininess );
		}
		else
		{
			vec3 reflectedWorldNorm = reflect(-lightDir, worldNormFixed);

			specularIntensity = uSpecular * pow( max(dot(reflectedWorldNorm, dirToCamera), 0), uShininess );
		}

		vec3 specLight = _Lights[i].color * specularIntensity;

		accumulatedLightColor += diffuseLight + specLight;
	}

	vec3 ambientLight = uAmbientLightColor * uAmbient;
	vec3 finalLightColor = ambientLight + accumulatedLightColor;

	vec4 texColor = texture(_Texture, fs_in.UV);

	FragColor = vec4(texColor.xyz * finalLightColor, texColor.w);
}