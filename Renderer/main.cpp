#include "Context.h"
#include "render.h"
#include "GLM/ext.hpp"

using namespace aie;
#include <iostream>
int main() {

	context window;
	window.init(640, 480, "Hello Window");

	//create a triangle
	vertex triVerts[] =
	{
		{// vertex 0
			{0,1,0,1},//vertex 0 position top
			{0,0,0,1},
			{.5,1},
			{0,0,1}
		},
		{
			{-.5,0,0,1},//bottom left
			{0,0,0,1},
			{0,0},
			{0,0,1}
		},
		{
			{.5,0,0,1},//botttom right
			{0,0,0,1},
			{1,0},
			{0,0,1}
		}
		//{
		//	{1,1,0,1},//top right
		//	{0,0,0,1},
		//	{0,0},
		//	{0,0,1}
		//}
	};
	/*vertex planeVerts[] = {
		{{-.5,.5,0,1}},
		{{-.5,-.5,0,1}},
		{{.5,-.5,0,1}},
		{{.5,.5,0,1}}
	};*/
	unsigned int triIndices[] = { 0,1,2 };
	//unsigned int planeIndices[] = { 0,1,2,0,2,3 };

	geometry basicTriangleGeo = makeGeometry(triVerts, 3, triIndices, 3);
	//create a shader
	/*const char* basicVert =
		"#version 430 core\n"
		"layout (location = 0) in vec4 position;\n"
		"layout (location = 1) in vec4 color;\n"
		"out vec4 vertColor;\n"
		"void main() {vertColor = color; gl_Position = position; }";
	const char* basicFrag =
		"#version 430 core\n"
		"in vec4 vertColor;\n"
		"out vec4 outColor;\n"
		"void main() { outColor = vertColor; }";*/
	shader basicShad = loadShader("res\\mvp.vert", "res\\mvp.frag");
	texture tritexture = loadTexture("res\\uvchecker.jpg");
	//shader basicShad = makeShader(basicVert, basicFrag);

	glm::mat4 tri_model = glm::identity<glm::mat4>();
	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 1, 5),
									 glm::vec3(0, 0, 0),
									 glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(glm::radians(60.0f), 640.0f / 480.0f, .1f, 100.0f);
	//update render loop
	while (!window.shouldClose()) {
		window.tick();
		window.clear();

		setuniform(basicShad, 0, cam_proj);
		setuniform(basicShad, 1, cam_view);
		setuniform(basicShad, 2, tri_model);
		setUniform(basicShad, 3, tritexture,0);

		draw(basicShad, basicTriangleGeo);
	}
	//destroy window
	window.term();
}