#version 430 core
in vec4 vertColor;

layout (location = 3) uniform sampler2D albedo;

out vec4 outColor;
void main() 
{ 
	outColor = vec4(1,0,0,1);
}