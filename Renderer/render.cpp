#include "render.h"

#include <iostream>
#include <fstream>
#include <string>

namespace aie {
	geometry makeGeometry(const vertex* verts, GLsizei vertCount, const GLuint* indeces, GLsizei indexCount) {
		//create new instance of geomitry
		geometry newGeo = {};
		newGeo.size = indexCount;
		//create buffers to store data
		glGenVertexArrays(1, &newGeo.vao);
		glGenBuffers(1, &newGeo.vbo);
		glGenBuffers(1, &newGeo.ibo);
		//bind buffers together
		glBindVertexArray(newGeo.vao);
		glBindBuffer(GL_ARRAY_BUFFER, newGeo.vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newGeo.ibo);
		//buffer data to the gpu
		glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(vertex), verts, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLsizei), indeces, GL_STATIC_DRAW);
		//describe the vertex data
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)sizeof(glm::vec4));

		//unbind buffers
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		//return the object
		return newGeo;
	}
	void freeGeometry(geometry& geo) {
		glDeleteBuffers(1, &geo.vbo);
		glDeleteBuffers(1, &geo.ibo);
		glDeleteVertexArrays(1, &geo.vao);

		geo = {};
	}


	shader makeShader(const char* vertSource, const char* fragSource) {
		//make shade robject
		shader newShade = {};
		//create shader program
		newShade.program = glCreateProgram();
		//create the shaders
		GLuint vert = glCreateShader(GL_VERTEX_SHADER);
		GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
		//load the souce code and compile it
		glShaderSource(vert, 1, &vertSource, 0);
		glShaderSource(frag, 1, &fragSource, 0);
		glCompileShader(vert);
		glCompileShader(frag);
		//attach the shaders to the shader program
		glAttachShader(newShade.program, vert);
		glAttachShader(newShade.program, frag);
		//link the program
		glLinkProgram(newShade.program);
		//delete the shaders(not the program)
		glDeleteShader(vert);
		glDeleteShader(frag);
		//return the shader object
		return newShade;
	}
	shader loadShader(const char* vertPath, const char* fragPath)
	{
		//load the shaders into strings
		

		std::string vertContents;
		std::string buffer;
		std::ifstream file(vertPath);
		if (file.is_open()) {
			while (std::getline(file, buffer)) {
				vertContents += buffer + "\n";
			}
		}
		file.close();

		std::string fragContents;
		file.open(fragPath);
		if (file.is_open()) {
			while (std::getline(file, buffer)) {
				fragContents += buffer + "\n";
			}
		}
		file.close();
		//call make shader and pass those strings

		//return the result of make shader
		return makeShader(vertContents.c_str(), fragContents.c_str());
	}
	void freeShader(shader& shad) {
		glDeleteProgram(shad.program);
	}

	void setuniform(const shader& shad, GLuint location, glm::mat4& value)
	{
		glProgramUniformMatrix4fv(shad.program, location, 1, GL_FALSE, &value[0][0]);
		
	}


	void draw(const shader& shad, const geometry& geo) {
		//bind shader program
		glUseProgram(shad.program);
		//bind vao
		glBindVertexArray(geo.vao);

		//draw the object
		glDrawElements(GL_TRIANGLES, geo.size, GL_UNSIGNED_INT, nullptr);
	}
}