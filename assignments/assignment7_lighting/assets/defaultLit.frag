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

#define MAX_LIGHTS 4

uniform Light _Lights[MAX_LIGHTS];

void main()
{
	vec3 norm = normalize(fs_in.WorldNormal);

	//light calcs done here

	FragColor = texture(_Texture,fs_in.UV);
}