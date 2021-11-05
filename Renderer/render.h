#pragma once

#include "GLEW/glew.h"
#include "GLM/glm.hpp"

namespace aie {
	struct vertex
	{
		glm::vec4 pos;
		glm::vec4 vertexColor;
	};
	struct geometry
	{
		GLuint vao, vbo, ibo;//ogl buffer names
		GLuint size;         //ogl index count
	};
	struct shader
	{
		GLuint program;
	};
	geometry makeGeometry(const vertex* verts, GLsizei vertCount, const GLuint* indeces, GLsizei indexCount);
	void freeGeometry(geometry& geo);

	shader makeShader(const char* vertSource, const char* fragSource);
	shader loadShader(const char* vertPath, const char* fragPath);
	void freeShader(shader& shad);

	void setuniform(const shader& shad, GLuint location, glm::mat4& value);

	void draw(const shader& shad, const geometry& geo);
}