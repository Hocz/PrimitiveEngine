#include "Block.h"
#include "Game.h"
#include "Player.h"
#include "TextureManager.h"
#include "Camera.h"

Block::Block(glm::vec2 position) 
	: Actor(position, glm::vec2(8))
{
	collisionType = ECollision_Type::Block;
}

void Block::Update()
{
	
}

void Block::Render()
{
	Actor::Render();

	TextureManager::Instance().Render("block_dirt", renderPosition.x, renderPosition.y, size.x, size.y, Game::Instance().GetRenderer(), Game::Instance().GetCamera()->zoom);

}

void Block::Hit(int damage)
{
	// health check

	Destroy();
}
