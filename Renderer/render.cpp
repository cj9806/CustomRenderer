#include "render.h"

#include <iostream>
#include <fstream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "STB/stb_image.h"
#include "GLM/ext.hpp"


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

	texture makeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char* pixels)
	{
		texture tex = { 0,width,height,channels };

		GLenum oglFormat = GL_RED;
		switch (channels) 
		{
		case 1:
			oglFormat = GL_RED;
			break;
		case 2:
			oglFormat = GL_RG;
			break;
		case 3:
			oglFormat = GL_RGB;
			break;
		case 4:
			oglFormat = GL_RGBA;
			break;
		default:
			oglFormat = GL_RED;
			break;
		}
		glGenTextures(1, &tex.handle);
		glBindTexture(GL_TEXTURE_2D, tex.handle);

		glTexImage2D(GL_TEXTURE_2D, //what texture
					 0, //mipmap level image quality
					 oglFormat, 
					 width, 
					 height, 
					 0,
					 oglFormat, 
					 GL_UNSIGNED_BYTE, 
					 pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		return tex;
	}

	void freeTexture(texture& tex)
	{
		glDeleteTextures(1, &tex.handle);
		tex = {};
	}


	texture loadTexture(const char* imagePath)
	{
		int width, height, format;
		unsigned char* rawPixelData = nullptr;
		stbi_set_flip_vertically_on_load(true);

		rawPixelData = stbi_load(imagePath, &width, &height, &format, STBI_default);

		texture tex = makeTexture(width, height, format, rawPixelData); 
		stbi_image_free(rawPixelData);

		return tex;
	}

	void setUniform(const shader& shad, GLuint location, const glm::mat4& value)
	{
		glProgramUniformMatrix4fv(shad.program, location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void setUniform(const shader& shad, GLuint location, const texture& value, int textureSlot)
	{

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