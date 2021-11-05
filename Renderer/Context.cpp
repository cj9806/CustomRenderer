#include "Context.h"
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

namespace aie {
	bool context::init(int width, int height, const char* title){
		//init glfw
		glfwInit();
		//create window
		window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		//designate specified window as rendering context
		glfwMakeContextCurrent(window);

		//init glew
		glewInit();
		// print out some diagnostics
		std::cout << "OpenGL Version: " << (const char*)glGetString(GL_VERSION) << std::endl;
		std::cout << "Renderer: " << (const char*)glGetString(GL_RENDERER) << std::endl;
		std::cout << "Vendor: " << (const char*)glGetString(GL_VENDOR) << std::endl;
		std::cout << "GLSL: " << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthFunc(GL_LEQUAL);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);

		glClearColor(0.25f, .25f, .25f, 1);

		return true;
	}
	void context::tick(){
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	void context::clear(){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void context::term(){
		//destroy window
		glfwDestroyWindow(window);
		//cleanp glfw
		glfwTerminate();
	}
	bool context::shouldClose() const {
		return glfwWindowShouldClose(window);
	}
}