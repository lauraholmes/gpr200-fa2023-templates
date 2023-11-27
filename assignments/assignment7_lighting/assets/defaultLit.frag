#version 450
out vec4 FragColor;

in Surface{
	vec2 UV;
	vec3 WorldPosition;
	vec3 WorldNormal;
}fs_in;

uniform sampler2D _Texture;
uniform vec3 _cameraPos;
uniform int _numLights;

struct Light
{
	vec3 position;
	vec3 color;
};
#define MAX_LIGHTS 4
uniform Light _Lights[MAX_LIGHTS];

struct Material {
	float ambientK;
	float diffuseK;
	float specular;
	float shininess;
};
uniform Material _material;

void main(){
	vec3 totalLight = vec3(0);
	FragColor = texture(_Texture,fs_in.UV);
	vec3 normal = normalize(fs_in.WorldNormal);

	for (int i = 0; i < _numLights; i++){
	//Diffuse
	vec3 lightDir = normalize(_Lights[i].position - fs_in.WorldPosition);
	float w = max(dot(lightDir, normal), 0);
	vec3 diffuse = _Lights[i].color * w;
	

	//BLINN SPEC
	vec3 view = normalize(_cameraPos - fs_in.WorldPosition);
	vec3 h = normalize(lightDir + view);
	vec3 specular = _Lights[i].color * pow(max(dot(h,normal),0), _material.shininess);

	//Ambient
	vec3 ambient = _Lights[i].color * _material.ambientK;

	//total
	vec3 lightColor = ambient + (_material.diffuseK * diffuse) + (_material.specular * specular);
	totalLight+=lightColor;
	}

	vec3 C = texture(_Texture,fs_in.UV).rgb;
	vec3 brick = C * totalLight;
	FragColor = vec4(brick,1);
}


