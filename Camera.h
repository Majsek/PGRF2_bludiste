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

	Square(float x_, float y_, float width_, float height_, int type_) {
		x = x_;
		y = y_;
		width = width_;
		height = height_;
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

// forward declaration
struct World;

struct Camera
{
	// Stores the main vectors of the camera
	glm::vec3 Position_;
	glm::vec3 Orientation{ 1.0f, 0.0f, 0.0f };
	glm::vec3 const Up{ 0.0f, 1.0f, 0.0f };

	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;
	std::vector<Square> squares_;

	World& world_;

	// Stores the WIDTH and HEIGHT of the window
	int width_;
	int height_;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed{ 0.1f };
	float sensitivity{ 50.0f };

	// Camera constructor to set up initial values
	//Camera(int WIDTH, int HEIGHT, glm::vec3 position, int(*map_)[20]);
	//Camera(int WIDTH, int HEIGHT, glm::vec3 position, bool map[20][20])
	//	: Position_{ position },
	//	width_{ WIDTH },
	//	height_{ HEIGHT },
	//	map_ { }
	//{ 	}


	Camera(int width, int height, glm::vec3 position, World& world)
		: Position_{ position },
		world_{ world },
		width_{ width },
		height_{ height }
	{}


	// Updates and exports the camera matrix to the Vertex Shader
	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	// Handles camera inputs
	void Inputs(GLFWwindow* window, float const delta_t);

	//Updates paper on collision
	void UpdatePaper(Square square);

	// Tries moving to the next position, checks collisions with walls
	void Try_move_on_pos(glm::vec3 nextPosition);
};