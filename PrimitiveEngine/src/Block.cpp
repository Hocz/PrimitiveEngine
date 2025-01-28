#include "Block.h"
#include "Game.h"
#include "Player.h"

Block::Block(glm::vec2 position) 
	: Actor(position, glm::vec2(16))
{
	collisionType = ECollision_Type::Block;
}

void Block::Update()
{
	
}

void Block::Render()
{
	Actor::Render();
}

void Block::Hit(int damage)
{
	// health check

	Destroy();
}
