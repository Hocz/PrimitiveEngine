#include "WorldGenerator.h"
#include "Block.h"
#include "glm.hpp"
#include <iostream>

WorldGenerator::WorldGenerator()
{
	GenerateWorld();
}

void WorldGenerator::GenerateWorld()
{
	for (int x = 0; x < WORLD_WIDTH; x++)
	{
		for (int y = 0; y < WORLD_HEIGHT; y++)
		{
			glm::vec2 position = glm::vec2(x * 8, y * 8);

			worldGrid[x][y] = new Block(position + glm::vec2(4, 4));
		}
	}
}

void WorldGenerator::DestoryBlockAtPos(int x, int y)
{
	if (worldGrid[x][y] != nullptr && !worldGrid[x][y]->GetIsDestroyed())
	{
		worldGrid[x][y]->Destroy();

		delete worldGrid[x][y];

		worldGrid[x][y] = nullptr;
	}
}

void WorldGenerator::CreateBlockAtPos(int x, int y)
{
	if (worldGrid[x][y] == nullptr)
	{
		glm::vec2 position = glm::vec2(x * 8, y * 8);

		worldGrid[x][y] = new Block(position + glm::vec2(4, 4));
	}
}

