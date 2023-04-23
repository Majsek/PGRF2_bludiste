#pragma once
#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	~Shader() { glDeleteProgram(ID); }

	// Activates the Shader Program
	void Activate();

	// Nastaví uniformní promìnnou pro matici 4x4
	void SetMat4(const std::string& name, const GLfloat* value);
};