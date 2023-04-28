#pragma once

#include "Camera.h"
#include "Wall.h"
#include "Texture.h"
#include "Paper.h"
#include "Table.h"

struct Object
{
	glm::mat4 trans_matrix;
	Texture const& texture;
	Geometry const& geometry;
};

constexpr auto const WIDTH{ 800 };
constexpr auto const HEIGHT{ 800 };

struct World
{
	// Creates int map
	// 0 nothing
	// 1 wall
	// 2 paper
	int  map_[20][20] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 4, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	WallGeometry wallgeometry;
	PaperGeometry papergeometry;
	TableGeometry tablegeometry;
	Texture walltext{ "wise_oak_tree.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE };
	Texture paperFtext{ "paperF.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE };
	Texture paperAtext{ "paperA.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE };
	Texture tabletext{ "table.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE };

	std::vector<Object> objects;

	// Create camera object
	Camera camera{ 800, 800, glm::vec3(2.0f, 3.5f, 1.5f), *this };

	World() { reset(); }

	float const tableWidth = 0.27f;
	float const tableHeight = 0.4f;
	float const tableOffset = -0.27f;

	void reset()
	{
		objects.clear();
		camera.squares_.clear();
		std::cout << "RESET";

		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (map_[i][j] == 0)
				{
					//std::cout << "nothing";
					continue;
				}
				else if (map_[i][j] == 1)
				{
					//std::cout << "wall";
					objects.emplace_back(
						glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0f, j)),
						walltext,
						wallgeometry.obj
					);
					camera.squares_.emplace_back(i + 0.5f, j + 0.5f, 0.65f, map_[i][j]);
				}
				else if (map_[i][j] == 2)
				{
					//std::cout << "paperF";
					objects.emplace_back(
						glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0f, j)),
						paperFtext,
						papergeometry.obj
					);
					camera.squares_.emplace_back(i + 0.5f, j + 0.5f, 0.4f, map_[i][j]);
				}
				else if (map_[i][j] == 3)
				{
					//std::cout << "paperA";
					objects.emplace_back(
						glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0f, j)),
						paperAtext,
						papergeometry.obj
					);
				}

				else if (map_[i][j] == 4)
				{
					//std::cout << "TABLE";
					objects.emplace_back(
						glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0f, j)),
						tabletext,
						tablegeometry.obj
					);
					camera.squares_.emplace_back(i + 0.5f + tableOffset, j + 0.5f, tableWidth, tableHeight, 4);
				}
				else if (map_[i][j] == 5)
				{
					//std::cout << "TABLE+PAPER_F";
					objects.emplace_back(
						glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.381f, j)),
						paperFtext,
						papergeometry.obj
					);
					objects.emplace_back(
						glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0f, j)),
						tabletext,
						tablegeometry.obj
					);
					camera.squares_.emplace_back(i + 0.5f, j + 0.5f, 0.4f, 2);
					camera.squares_.emplace_back(i + 0.5f + tableOffset, j + 0.5f, tableWidth, tableHeight, 4);
				}
				else if (map_[i][j] == 6)
				{
					//std::cout << "TABLE+PAPER_A";
					objects.emplace_back(
						glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.381f, j)),
						paperAtext,
						papergeometry.obj
					);
					objects.emplace_back(
						glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0f, j)),
						tabletext,
						tablegeometry.obj
					);
					camera.squares_.emplace_back(i + 0.5f + tableOffset, j + 0.5f, tableWidth, tableHeight, 4);
				}

			}
		}
	}
};