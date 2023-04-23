#pragma once
#include<glad/glad.h>

#include <utility>

class VBO
{
	// Reference ID of the Vertex Buffer Object
	GLuint ID{};
public:
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(GLfloat const* vertices, GLsizeiptr count)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	}

	VBO(VBO&& other) noexcept
	{
		std::swap(ID, other.ID);
	}

	VBO(VBO const&) = delete;
	VBO& operator=(VBO const&) = delete;
	VBO& operator=(VBO&&) = delete;

	~VBO() { if (ID) { glDeleteBuffers(1, &ID); } }

	void Bind() { glBindBuffer(GL_ARRAY_BUFFER, ID); }
	void Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
};