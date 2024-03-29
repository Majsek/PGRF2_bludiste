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
	glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(obj.model_matrix));
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
	// In this case the viewport goes from x = 0, y = 0
	glViewport(0, 0, WIDTH, HEIGHT);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");


	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);


	int const modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
	GLint randomLoc = glGetUniformLocation(shaderProgram.ID, "random");
	GLint fogRangeLoc = glGetUniformLocation(shaderProgram.ID, "fogRange");
	

	double prevTime = glfwGetTime();

	World my_world;

	shaderProgram.Activate();

	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// Initial flame value
	float flame = 0.7f;
	float fogRange = 0.5;
	glUniform1f(fogRangeLoc, fogRange);

	// Enemy speed
	float enemy_speed = 0.5f;

	bool game_over = false;

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		if (game_over)
		{
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwDestroyWindow(window);
				return 0;
			}

			glfwPollEvents();
		}
		else
		{

		
		//set fog range
		fogRange = 0.5 + 0.2 * my_world.paperCounter;
		enemy_speed = 0.5 + 0.1 * my_world.paperCounter;
		glUniform1f(fogRangeLoc, fogRange);

		glfwSetWindowTitle(window, ((char const*)u8"Po�et opraven�ch z�po�t�: " + std::to_string(my_world.paperCounter) + "/5").c_str());

		// Timer
		double delta_t = glfwGetTime() - prevTime;
		prevTime = glfwGetTime();

		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Handles camera inputs
		my_world.camera.Inputs(window, static_cast<float>(delta_t));
		// Updates and exports the camera matrix to the Vertex Shader
		my_world.camera.Matrix(60.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");


		// Random flame change
		static double time_acc = 0.0;
		time_acc += delta_t;
		constexpr auto const FLAME_RATE{ 60.0 };
		constexpr auto const FLAME_PERIOD{ 1.0 / FLAME_RATE };
		if (time_acc > FLAME_PERIOD)
		{
			time_acc -= FLAME_PERIOD;
			flame += (rand() % 100 - 50) * 0.001f;
		}

		// Flame range limiter 0.6f-1.0f
		flame = std::max(flame, 0.7f);
		flame = std::min(flame, 1.0f);

		glUniform1f(randomLoc, flame);

		// Enemy
		if (my_world.paperCounter > 0)
		{

			glm::mat4 enemy_mat4 = my_world.enemy.model_matrix;
			glm::vec3 enemy_vec3 = glm::vec3(enemy_mat4[3].x, enemy_mat4[3].y, enemy_mat4[3].z);

			glm::vec3 direction = glm::normalize(enemy_vec3 - my_world.camera.Position_);
			direction.y = 0.0f;

			float distance = static_cast<float>(enemy_speed * delta_t);

			auto const cam_pos = glm::vec2{ my_world.camera.Position_.x,  my_world.camera.Position_.z };
			auto const pos = glm::vec2{ enemy_vec3.x, enemy_vec3.z };

			auto const enemy_vec = cam_pos - pos;
			auto const enemy_dist = (enemy_vec.x * enemy_vec.x + enemy_vec.y * enemy_vec.y);
			if (enemy_dist < 6.0f && enemy_dist > (5.0f - 0.7*my_world.paperCounter))
			{
				distance = 0.005f;// glm::length(cam_pos - pos);
			}

			if (enemy_dist < 1.0f && enemy_dist >(0.1f))
			{
				distance = 0.005f;// glm::length(cam_pos - pos);
			}

			//GAME OVER
			if (enemy_dist < 0.1f)
			{
				glfwSetWindowTitle(window, (
					(char const*)u8"Spravedlnost t� dohnala! Fal�ov�n� z�po�tov�ch test� ti vydr�elo celkem: "
					+ std::to_string(glfwGetTime()) +
					" sekund a stihl jsi opravit celkem " +
					std::to_string(my_world.paperCounter) +
					(char const*)u8"/5 z�po�tov�ch test�").c_str());
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				game_over = true;
			}
			else if (my_world.paperCounter == 5)
			{
				glfwSetWindowTitle(window, (
					(char const*)u8"Utekl jsi spravedlnosti! Zfal�ov�n� v�ech z�po�tov�ch test� ti zabralo celkem: "
					+ std::to_string(glfwGetTime()) +
					" sekund ").c_str());
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				game_over = true;
			}

			glm::vec3 new_position = enemy_vec3 - direction * distance;

			my_world.enemy.model_matrix = glm::mat4{1.f};
			my_world.enemy.model_matrix[3] = glm::vec4(new_position, 1.0f);


			my_world.enemy.model_matrix *= glm::rotate(glm::orientedAngle(glm::normalize(cam_pos - pos), glm::vec2(1.0f, 0.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
			draw_object(my_world.enemy, modelLoc);
		}
	



		//Draw objects
		for (auto const& obj : my_world.objects)
		{
			draw_object(obj, modelLoc);
		}
		draw_object(my_world.floor, modelLoc);
		draw_object(my_world.ceiling, modelLoc);
		
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
		}
	}

	// Delete window before ending the program
	glfwDestroyWindow(window);
	return 0;
}

