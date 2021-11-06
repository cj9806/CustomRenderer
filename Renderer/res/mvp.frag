#version 430 core
in vec4 vertColor;

input (location = 3) uniform sampler2D albedo;

out vec4 outColor;
void main() 
{ 
	outColor = texture(albedo, vUV);
}