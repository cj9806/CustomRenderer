#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 UVs;
layout (location = 3) in vec3 normals;

layout (location = 0) uniform mat4 proj;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 model;

out vec4 vertColor;
out vec2 vUV;
void main()
{
	gl_Position = proj * view * model * position;
	vertColor = color;
	vUV = UVs;
}