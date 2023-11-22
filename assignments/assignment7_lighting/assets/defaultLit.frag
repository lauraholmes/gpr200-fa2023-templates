#version 450
out vec4 FragColor;

in Surface{
	vec2 UV;
	vec3 WorldPosition;
	vec3 WorldNormal;
}fs_in;

uniform sampler2D _Texture;

void main(){
	FragColor = texture(_Texture,fs_in.UV);
	vec3 normal = normalize(fs_in.WorldNormal);

}