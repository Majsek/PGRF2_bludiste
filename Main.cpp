#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include "Wall.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <filesystem>
#include "Paper.h"
namespace fs = std::filesystem;

const unsigned int width = 800;
const unsigned int height = 800;

struct Object
{
	glm::mat4 trans_matrix;
	Texture const& texture;
	Geometry const& geometry;
};

void draw_object(Object const& obj, int model_location)
{
	obj.geometry.vao.Bind();
	obj.texture.Bind();
	glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(obj.trans_matrix));
	glDrawElements(GL_TRIANGLES, obj.geometry.index_num, GL_UNSIGNED_INT, 0);
};

struct glfw
{
	glfw()
	{
		// Initialize GLFW
		glfwInit();
	}

	~glfw()
	{
		// Terminate GLFW before ending the program
		glfwTerminate();
	}
};

int main()
{
	glfw my_glfw;

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels
	GLFWwindow* window = glfwCreateWindow(width, height, "Bludiste", nullptr, nullptr);
	// Error check if the window fails to create
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	WallGeometry wall_geometry;
	PaperGeometry paper_geometry;

	Texture brick_texture("wise_oak_tree.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
	Texture paper_texture("paperF1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Initializes matrices so they are not the null matrix
	glm::mat4 transMat{ 1.0f };

	// Creates int map
	// 0 nothing
	// 1 wall
	// 2 paper
	int  map_[20][20] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	// Creates camera object
	Camera camera(width, height, glm::vec3(2.0f, 3.5f, 1.5f), map_);

	int const modelLoc = glGetUniformLocation(shaderProgram.ID, "model");

	double prevTime = glfwGetTime();


	std::vector<Object> objects;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (map_[i][j] == 0)
			{
				continue;
			}
			else if(map_[i][j] == 1)
			{
			objects.emplace_back(
				glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0f, j)),
				brick_texture,
				wall_geometry.obj
			);
			camera.squares_.emplace_back(i + 0.5f, j + 0.5f, 0.65f, map_[i][j]);
			}
			else
			{
			objects.emplace_back(
				glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0f, j)),
				paper_texture,
				paper_geometry.obj
			);
			camera.squares_.emplace_back(i + 0.5f, j + 0.5f, 0.4f, map_[i][j]);
			}
		}
	}



	//for (const auto& object : objects) {

	//	std::cout << typeid(object.geometry).name() << " \n";
	//	for (int i = 0; i < 4; i++) {
	//		for (int j = 0; j < 4; j++) {
	//			std::cout << object.trans_matrix[i][j] << " ";
	//		}
	//		std::cout << std::endl;
	//	}

	//}


	shaderProgram.Activate();

	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Timer
		double delta_t = glfwGetTime() - prevTime;
		prevTime = glfwGetTime();

		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Handles camera inputs
		camera.Inputs(window, static_cast<float>(delta_t));
		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(70.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		for (auto const& obj : objects)
		{
			draw_object(obj, modelLoc);
		}

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete window before ending the program
	glfwDestroyWindow(window);
	return 0;
}