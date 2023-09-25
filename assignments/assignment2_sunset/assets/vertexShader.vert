
	#version 450
	uniform vec4 vColor;
	uniform vec3 vPos;

	layout(location = 0) in vec3 vPos;
	layout(location = 1) in vec4 vColor;

	out vec4 Color;

	void main(){
		gl_Position = vec4(vPos,1.0);
		Color = vColor;
	}