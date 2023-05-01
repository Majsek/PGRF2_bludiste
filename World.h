#pragma once

#include "Camera.h"
#include "Wall.h"
#include "Texture.h"
#include "Paper.h"
#include "Table.h"
#include "Enemy.h"
#include "Floor.h"
#include <cstdlib>

struct Object
{
	glm::mat4 model_matrix;
	Texture const& texture;
	Geometry const& geometry;
};

constexpr auto const WIDTH{ 1280 };
constexpr auto const HEIGHT{ 720 };

struct World
{
	// Creates int map
	// 0 nothing
	// 1 wall
	// 4 table
	// 5 paper
	int map_[20][20] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{ 1, 0, 0, 0, 0, 1, 4, 4, 4, 0, 0, 4, 4, 4, 1, 0, 4, 4, 4, 1},
	{ 1, 4, 0, 5, 4, 1, 4, 4, 4, 0, 0, 4, 4, 5, 1, 0, 4, 4, 4, 1},
	{ 1, 4, 0, 4, 4, 1, 4, 4, 4, 0, 0, 4, 4, 4, 1, 0, 4, 5, 4, 1},
	{ 1, 4, 0, 4, 4, 1, 4, 4, 4, 0, 0, 4, 4, 4, 1, 0, 4, 4, 4, 1},
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 4, 4, 0, 4, 4, 4, 1, 0, 0, 0, 0, 1, 4, 4, 4, 0, 4, 4, 1},
	{ 1, 4, 4, 0, 4, 4, 4, 1, 0, 0, 0, 0, 1, 4, 4, 4, 0, 4, 4, 1},
	{ 1, 4, 4, 0, 4, 4, 4, 1, 0, 0, 0, 0, 1, 4, 4, 4, 0, 4, 4, 1},
	{ 1, 4, 4, 0, 4, 4, 5, 1, 0, 0, 0, 0, 1, 4, 4, 4, 0, 5, 4, 1},
	{ 1, 4, 4, 0, 4, 4, 4, 1, 0, 0, 0, 0, 1, 4, 4, 4, 0, 4, 4, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	WallGeometry wallgeometry;
	PaperGeometry papergeometry;
	TableGeometry tablegeometry;
	EnemyGeometry enemyegeometry;
	FloorGeometry flooregeometry;
	Texture enemytext{ "enemy.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE };
	Texture walltext{ "wallBrick.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE };
	Texture floortext{ "floor.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE };
	Texture paperFtext{ "paperF.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE };
	Texture paperAtext{ "paperA.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE };
	Texture tabletext{ "table.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE };

	std::vector<Object> objects;

	int paperCounter = 0;

	// Create camera object
	Camera camera{ WIDTH, HEIGHT, glm::vec3(18.5f, 0.6f, 10.f), *this };

	World() { reset(); }

	float const tableWidth = 0.27f;
	float const tableHeight = 0.4f;
	float const tableOffset = -0.27f;


	Object floor{
		glm::mat4(1.0f),
		floortext,
		flooregeometry.obj
	};

	Object ceiling{
		glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 1.5f, 0.f)),
		floortext,
		flooregeometry.obj
	};

	Object enemy{
		glm::translate(glm::mat4(1.0f), glm::vec3(-10.f, 0.0f, -10.f)),
		enemytext,
		enemyegeometry.obj
	};



	void reset()
	{
		if (paperCounter > 0)
		{
			int random_spawn = rand() % 2 == 0 ? 1 : -1;
			enemy.model_matrix[3] = glm::vec4(glm::vec3(camera.Position_.x + (5 - 0.5*paperCounter) * random_spawn, 0.f, camera.Position_.z + (5 - 0.5 * paperCounter) * random_spawn), 1.0f);
		}


		objects.clear();
		camera.squares_.clear();

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
					objects.emplace_back(
						glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.01f, j)),
						paperFtext,
						papergeometry.obj
					);
					camera.squares_.emplace_back(i + 0.5f, j + 0.5f, 0.1f, map_[i][j]);
				}
				else if (map_[i][j] == 3)
				{
					//std::cout << "paperA";
					objects.emplace_back(
						glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.01f, j)),
						paperAtext,
						papergeometry.obj
					);
				}

				else if (map_[i][j] == 4)
				{
					objects.emplace_back(
						glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0f, j)),
						tabletext,
						tablegeometry.obj
					);
					camera.squares_.emplace_back(i + 0.5f + tableOffset, j + 0.5f, tableWidth, tableHeight, 4);
				}
				else if (map_[i][j] == 5)
				{
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