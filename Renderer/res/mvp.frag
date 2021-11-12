#version 430 core
in vec4 vertColor;

// shader uniforms
layout (location = 3) uniform sampler2D albedo;

//input attributes
in vec2 vUV;

//output
out vec4 outColor;
void main() 
{ 
	outColor = texture(albedo, vUV);
}