//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"



const unsigned int width = 800;
const unsigned int height = 800;



// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	//bottom
	0.0f, 0.0f,  1.0f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	0.0f, 0.0f, 0.0f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,

	 1.0f, 0.0f, 0.0f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,

	//top
	0.0f, 1.0f,  1.0f,     0.83f, 0.70f, 0.44f,	1.0f, 1.0f,
	0.0f, 1.0f, 0.0f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,

	 1.0f, 1.0f, 0.0f,     0.83f, 0.70f, 0.44f,	1.0f, 1.0f,
	 1.0f, 1.0f,  1.0f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,
};
//{ //     COORDINATES     /        COLORS      /   TexCoord  //
	//bottom
	//-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	//-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,

	// 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	// 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,

	//top
//	-0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 1.0f,
//	-0.5f, 1.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,

	// 0.5f, 1.0f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 1.0f,
	// 0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,
//};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 4,
	1, 5, 4,

	7, 3, 0,
	0, 4, 7,

	2, 3, 7,
	2, 7, 6,

	1, 2, 6,
	6, 5, 1,
};


int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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


	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();



	/*
	* I'm doing this relative path thing in order to centralize all the resources into one folder and not
	* duplicate them between tutorial folders. You can just copy paste the resources from the 'Resources'
	* folder and then give a relative path from this folder to whatever resource you want to get to.
	* Also note that this requires C++17, so go to Project Properties, C/C++, Language, and select C++17
	*/
	//std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	//std::string texPath = "/Resources/YoutubeOpenGL 7 - Going 3D/";

	// Texture
	//Texture brickTex((parentDir + texPath + "wise_oak_tree.jpg").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	//brickTex.texUnit(shaderProgram, "tex0", 0);

	// Original code from the tutorial
	Texture brickTex("wise_oak_tree.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);

	Texture paperTex("paperF1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	paperTex.texUnit(shaderProgram, "tex1", 0);



	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);



	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Initializes matrices so they are not the null matrix
	glm::mat4 transMat{ 1.0f };

	// Creates a bool map
	bool  map_[20][20] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	// Creates camera object
	Camera camera(width, height, glm::vec3(2.0f, 3.5f, 1.5f), map_);

	int const modelLoc = glGetUniformLocation(shaderProgram.ID, "model");

	double prevTime = glfwGetTime();

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Timer
		double delta_t = glfwGetTime() - prevTime;
		prevTime = glfwGetTime();

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		shaderProgram.Activate();

		// Assigns different transformations to each matrix
		//model = glm::rotate(model, glm::radians(static_cast<float>(100.*delta_t)), glm::vec3(0.0f, 0.0f, 1.0f));

		// Outputs the matrices into the Vertex Shader
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);

		// Handles camera inputs
		camera.Inputs(window, static_cast<float>(delta_t));
		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(70.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
		/*std::cout << glm::to_string(camera.Position_) << std::endl;
		std::cout << "\n";*/

		// Binds texture so that is appears in rendering
		brickTex.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();

		// Draw primitives, number of indices, datatype of indices, index of indices
		//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);


		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (!map_[i][j])
				{
					continue;
				}
				transMat = glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0f, j));

				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transMat));

				glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
			}
		}
		paperTex.Bind();

		transMat = glm::translate(glm::mat4(1.0f), glm::vec3(3, 0.0f, 3));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transMat));

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//glm::mat4 model2 = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	brickTex.Delete();
	paperTex.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}