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
		/*vertex structure*/
		//start back face
		{{-.5,.5,.5,1},{0,0,0,1},{0,1},{0,0,1}},
		{{-.5,-.5,.5,1},{0,0,0,1},{0,0},{0,0,1}},
		{{.5,-.5,.5,1},{0,0,0,1},{1,0},{0,0,1}},
		{{.5,.5,.5,1},{0,0,0,1},{1,1},{0,0,1}},
		//end face 1

		//start face2
		{{.5,.5,-.5,1},{0,0,0,1},{0,1},{1,0,0}},
		{{.5,-.5,-.5,1},{0,0,0,1},{0,0},{1,0,0}},
		{{.5,-.5,.5,1},{0,0,0,1},{1,0},{1,0,0}},
		{{.5,.5,.5,1},{0,0,0,1},{1,1},{1,0,0}},
		//end face 2

		//start face 3
		{{.5,.5,-.5,1},{0,0,0,1},{0,1},{0,0,-1}},
		{{.5,-.5,-.5,1},{0,0,0,1},{0,0},{0,0,-1}},
		{{-.5,-.5,-.5,1},{0,0,0,1},{1,0},{0,0,-1}},
		{{-.5,.5,-.5,1},{0,0,0,1},{1,1},{0,0,-1}},
		//end face 3

		//start face 4
		{{-.5,.5,-.5,1},{0,0,0,1},{0,1},{-1,0,0}},
		{{-.5,-.5,-.5,1},{0,0,0,1},{0,0},{-1,0,0}},
		{{-.5,-.5,.5,1},{0,0,0,1},{1,0},{-1,0,0}},
		{{-.5,.5,.5,1},{0,0,0,1},{1,1},{-1,0,0}},
		//end face 4

		//start face 5
		{{-.5,.5,-.5,1},{0,0,0,1},{0,1},{0,1,0}},
		{{.5,.5,-.5,1},{0,0,0,1},{0,0},{0,1,0}},
		{{.5,.5,.5,1},{0,0,0,1},{1,0},{0,1,0}},
		{{-.5,.5,.5,1},{0,0,0,1},{1,1},{0,1,0}},
		//end face 5

		//start face 6
		{{-.5,-.5,-.5,1},{0,0,0,1},{0,1},{0,-1,0}},
		{{.5,-.5,-.5,1},{0,0,0,1},{0,0},{0,-1,0}},
		{{.5,-.5,.5,1},{0,0,0,1},{1,0},{0,-1,0}},
		{{-.5,-.5,.5,1},{0,0,0,1},{1,1},{0,-1,0}}
		//end face 6
	};
	
	unsigned int triIndices[] = { 0,1,2,0,2,3,
								  7,6,4,6,5,4,
								  8,9,10,8,10,11,
								  12,13,14,12,14,15,
								  19,18,16,18,17,16,
								  20,21,22,20,22,23};
	/*unsigned int triIndices[] = { 0,1,2,0,2,3,
							  4,5,6,4,6,7 };*/
	//unsigned int planeIndices[] = { 0,1,2,0,2,3 };

	geometry basicTriangleGeo = makeGeometry(triVerts, 24, triIndices, 36);
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

	glm::vec3 ambLight = glm::vec3(.2f, .2f, .2f);
	glm::vec3 dirLight = glm::normalize(glm::vec3(-1, -1, -1));
	//shader basicShad = makeShader(basicVert, basicFrag);

	glm::mat4 tri_model = glm::identity<glm::mat4>();
	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 1, 5),
									 glm::vec3(0, 1, 0),
									 glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(glm::radians(60.0f), 640.0f / 480.0f, .1f, 100.0f);
	//update render loop
	while (!window.shouldClose()) {
		window.tick();
		window.clear();

		tri_model = glm::rotate(tri_model, .05f, glm::vec3(0, .25, 0));
		tri_model = glm::rotate(tri_model, .05f, glm::vec3(0, 0, -.25));
		setUniform(basicShad, 0, cam_proj);
		setUniform(basicShad, 1, cam_view);
		setUniform(basicShad, 2, tri_model);
		setUniform(basicShad, 3, tritexture,0);
		setUniform(basicShad, 4, ambLight);
		setUniform(basicShad, 5, dirLight);

		draw(basicShad, basicTriangleGeo);
	}
	//destroy window
	window.term();
}