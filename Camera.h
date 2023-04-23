#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include<vector>

#include"shaderClass.h"

struct Square {
	float x;
	float y;
	float width;
	float height;
	int type;

	Square(float x_, float y_, float size, int type_) {
		x = x_;
		y = y_;
		width = size;
		height = size;
		type = type_;
	}

	bool Intersects(float xx, float yy) const
	{
		return (x < xx + width
			&& x + width > xx
			&& y < yy + height
			&& y + height > yy);
	}
};

struct Camera
{
	// Stores the main vectors of the camera
	glm::vec3 Position_;
	glm::vec3 Orientation{ 1.0f, 0.0f, 0.0f };
	glm::vec3 const Up{ 0.0f, 1.0f, 0.0f };

	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;
	std::vector<Square> squares_;


	// Stores the width and height of the window
	int width_;
	int height_;


	bool map_[20][20];

	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed{ 0.1f };
	float sensitivity{ 50.0f };

	// Camera constructor to set up initial values
	Camera(int width, int height, glm::vec3 position, int map[20][20]);
	//Camera(int width, int height, glm::vec3 position, bool map[20][20])
	//	: Position_{ position },
	//	width_{ width },
	//	height_{ height },
	//	map_ { }
	//{ 	}

	// Updates and exports the camera matrix to the Vertex Shader
	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	// Handles camera inputs
	void Inputs(GLFWwindow* window, float const delta_t);

	// Tries moving to the next position, checks collisions with walls
	void Try_move_on_pos(glm::vec3 nextPosition);
};