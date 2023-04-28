#include"Camera.h"

#include "World.h"


void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position_, Position_ + Orientation, Up);

	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), static_cast<float>(width_) / height_, nearPlane, farPlane);

	// Exports the camera matrix to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}



void Camera::Inputs(GLFWwindow* window, float const delta_t)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Try_move_on_pos(speed * delta_t * Orientation);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Try_move_on_pos(speed * delta_t * -glm::normalize(glm::cross(Orientation, Up)));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Try_move_on_pos(speed * delta_t * -Orientation);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Try_move_on_pos(speed * delta_t * glm::normalize(glm::cross(Orientation, Up)));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Try_move_on_pos(speed * delta_t * Up);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Try_move_on_pos(speed * delta_t * -Up);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 2.f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 1.f;
	}


	 //Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		 //Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (width_ / 2), (height_ / 2));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (height_ / 2)) / height_;
		float rotY = sensitivity * (float)(mouseX - (width_ / 2)) / width_;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (width_ / 2), (height_ / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}

	
}


void Camera::UpdatePaper(Square square) {
	std::cout << "Zápoèet opraven\n";
	square.type = 3;
	world_.map_[static_cast<int>(square.x - 0.5f)][static_cast<int>(square.y - 0.5f)] = 3;
	world_.reset();
}


auto Intersects(float square_p, float p, float offset) -> bool
{
	return square_p < p + offset && square_p + offset > p;
}

//Collisions
void Camera::Try_move_on_pos(glm::vec3 nextPosition) {
	glm::vec2 newPosition = glm::vec2(Position_.x, Position_.z) + glm::vec2(nextPosition.x, nextPosition.z);

	int i = -1;
	for (Square& square : squares_) {
		++i;
		if (square.Intersects(newPosition.x, newPosition.y))
		{
			newPosition = [&newPosition, &i, &square, this]
			{
				auto new_pos{ newPosition };
				if (Intersects(square.x, Position_.x, square.width))
				{
					if (square.type == 2)
					{
						UpdatePaper(square);
						return new_pos;
					}
					else if (square.type == 3)
					{
						return new_pos;
					}
					new_pos.y = Position_.z;
				}

				if (Intersects(square.y, Position_.z, square.height))
				{
					if (square.type == 2)
					{
						UpdatePaper(square);
						return new_pos;
					}
					else if (square.type == 3)
					{
						return new_pos;
					}
					new_pos.x = Position_.x;
					
				}

				return new_pos;
			}();
		}
	}

	// Move
	Position_ = glm::vec3(newPosition.x, 0.5f, newPosition.y);
}
