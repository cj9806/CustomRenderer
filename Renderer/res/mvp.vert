#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

layout (location = 0) uniform mat4 proj;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 model;
out vec4 vertColor;

void main()
{
	gl_Position = proj * view * model * position;
	vertColor = color;
}