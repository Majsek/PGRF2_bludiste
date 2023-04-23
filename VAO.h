#pragma once
#include "VBO.h"

#include <glad/glad.h>

#include <utility>

class VAO
{
	// ID reference for the Vertex Array Object
	GLuint ID{};
public:
	VAO()
	{
		glGenVertexArrays(1, &ID);
		Bind();
	}

	VAO(VAO&& other) noexcept
	{
		std::swap(ID, other.ID);
	}

	VAO(VAO const&) = delete;
	VAO& operator=(VAO const&) = delete;
	VAO& operator=(VAO&&) = delete;

	~VAO() { if (ID) { glDeleteVertexArrays(1, &ID); } }

	// Links a VBO Attribute such as a position or color to the VAO
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset)
	{
		VBO.Bind();
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		VBO.Unbind();
	}

	void Bind() const { glBindVertexArray(ID); }
	void Unbind() const { glBindVertexArray(0); }
};