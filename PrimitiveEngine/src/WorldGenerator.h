#pragma once

#include "Block.h"

class Actor;

class WorldGenerator
{
public:

	WorldGenerator();


	void GenerateWorld();

	void DestoryBlockAtPos(int x, int y);
	void CreateBlockAtPos(int x, int y);

	// world data
	static constexpr int WORLD_WIDTH = 50;
	static constexpr int WORLD_HEIGHT = 20;

	Block* worldGrid[WORLD_WIDTH][WORLD_HEIGHT] = { nullptr };

private:

	

};
