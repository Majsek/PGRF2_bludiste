#pragma once
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

#include <glad/glad.h>

#include <array>

#include <cstdint>

struct Geometry
{
	GLsizei index_num;
	VAO vao; // Nastaveni zpusobu cteni VBO
	VBO vbo; // Buffer obsahujici data vrcholu
	EBO ebo; // Buffer obsahujici indexy vrcholu

	template<std::size_t VertNum, std::size_t IndNum>
	static Geometry create(std::array<GLfloat, VertNum> vertices, std::array<GLuint, IndNum> indices)
	{
		Geometry obj{ IndNum, {}, { vertices.data(), vertices.size() }, { indices.data(), indices.size() } };

		// Links VBO attributes such as coordinates and colors to VAO
		obj.vao.LinkAttrib(obj.vbo, 0, 3, GL_FLOAT, 5 * sizeof(GLfloat), (void*)0);
		//obj.vao.LinkAttrib(obj.vbo, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
		obj.vao.LinkAttrib(obj.vbo, 1, 2, GL_FLOAT, 5 * sizeof(GLfloat), (void*)(3 * sizeof(float)));

		//obj.vao.LinkAttrib(obj.vbo, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
		//obj.vao.LinkAttrib(obj.vbo, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
		//obj.vao.LinkAttrib(obj.vbo, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(float)));

		// Unbind vao to prevent accidentally modifying it
		obj.vao.Unbind();

		return obj;
	}
};