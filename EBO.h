#pragma once

#include<glad/glad.h>

#include <utility>

class EBO
{
	// ID reference of Elements Buffer Object
	GLuint ID{};
public:
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(GLuint const* indices, GLsizeiptr size)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), indices, GL_STATIC_DRAW);
	}

	EBO(EBO&& other) noexcept
	{
		std::swap(ID, other.ID);
	}

	EBO(EBO const&) = delete;
	EBO& operator=(EBO const&) = delete;
	EBO& operator=(EBO&&) = delete;

	~EBO() { if (ID) { glDeleteBuffers(1, &ID); } }

	void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); }
	void Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
};