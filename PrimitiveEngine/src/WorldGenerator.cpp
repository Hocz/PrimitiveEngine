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
			glm::vec2 position = glm::vec2(x * 16, y * 16);

			worldGrid[x][y] = new Block(position + glm::vec2(8, 8));
		}
	}
}

void WorldGenerator::DestoryBlockAtPos(int x, int y)
{
	if (worldGrid[x][y]->GetIsDestroyed() && worldGrid[x][y] != nullptr)
	{
		delete worldGrid[x][y];

		worldGrid[x][y] = nullptr;
	}
}

