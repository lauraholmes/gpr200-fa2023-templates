

#version 450
out vec4 FragColor;
uniform vec3 _Color;
uniform float _Brightness;
in vec2 UV;
uniform vec3      iResolution;           // viewport resolution (in pixels)
uniform float     iTime;                 // shader playback time (in seconds)
uniform float     iTimeDelta;            // render time (in seconds)
uniform float     iFrameRate;            // shader frame rate
uniform int       iFrame;                // shader playback frame
uniform float     iChannelTime[4];       // channel playback time (in seconds)
uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
out vec4 fragColor;
in vec2 fragCoord;
float circleSDF(vec2 p, float r){
    return length(p)-r;
}


void main(){
	FragColor = vec4(_Color * _Brightness,1.0);
	    vec2 uv = (2.0*fragCoord-iResolution.xy)/iResolution.y;
    
    
    float edge = sin(iTime)*0.7 + 0.1;
    float t = smoothstep(edge-0.05,edge+0.05,uv.y);
    
    
     //BG gradient
vec3 color = mix(vec3(1.0,0.5,0.0),vec3(1.0,0.9,0.5),uv.y);
    
//Get 0-1 T value for hill shape
float hills = 1.0 - step(sin(uv.x*5.0) * 0.2 - 0.4,uv.y);
    
//Blend dark grey hills
color = mix(color,vec3(0.2),hills);
        

    fragColor = vec4(t,color);
vec2 circlePos = vec2(cos(iTime),sin(iTime));
float circleRadius = 0.2;
float d = circleSDF(uv - circlePos,circleRadius);

    
    
//Draw red circle
vec4 circleAColor = vec4(1.0,0.2,0.3,1.0);
color = mix(color,circleAColor.rgb,d * circleAColor.a);
//Draw blue circle
vec4 circleBColor = vec4(0.2,0.6,1.0,0.7);
color = mix(color,circleBColor.rgb,d * circleBColor.a);
// Output to screen
fragColor = vec4(color,1.0);
}