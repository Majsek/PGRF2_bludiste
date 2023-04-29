#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include "Wall.h"
#include "World.h"

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
#include <random>
namespace fs = std::filesystem;


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
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Bludiste", nullptr, nullptr);
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
	glViewport(0, 0, WIDTH, HEIGHT);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");


	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Initializes matrices so they are not the null matrix
	//glm::mat4 transMat{ 1.0f };




	int const modelLoc = glGetUniformLocation(shaderProgram.ID, "model");

	GLint randomLoc = glGetUniformLocation(shaderProgram.ID, "random");
	

	double prevTime = glfwGetTime();

	World my_world;



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






	// Nastavení semínka pro generátor náhodných èísel
	srand(time(0));

	// Initial flame value
	float flame = 0.7f;

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Timer
		double delta_t = glfwGetTime() - prevTime;
		prevTime = glfwGetTime();

		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Handles camera inputs
		my_world.camera.Inputs(window, static_cast<float>(delta_t));
		// Updates and exports the camera matrix to the Vertex Shader
		my_world.camera.Matrix(70.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		std::cout << "\n Camera pos: \n" << my_world.camera.Position_.x << std::endl;
		std::cout << my_world.camera.Position_.z << std::endl;

		// Random flame change
		flame += ((rand() % 100 - 50) / 10.0f) * delta_t;

		// Flame range limiter 0.6f-1.0f
		flame = std::max(flame, 0.6f);
		flame = std::min(flame, 1.0f);

		glUniform1f(randomLoc, flame);

		//std::cout << "Flame value: " << flame << std::endl;


		for (auto const& obj : my_world.objects)
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

