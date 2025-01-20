#include "Block.h"
#include "Game.h"
#include "AABB.h"
#include "Player.h"

Block::Block(glm::vec2 position) 
	: Actor(position, glm::vec2(16))
{
	collisionType = ECollision_Type::Block;
}

void Block::Update()
{
	if (game->GetPlayer() != nullptr)
	{
		Actor* player = game->GetCollidingActor(this, ECollision_Type::Player);
		if (player)
		{			
			AABB b = AABB::FromPositionSize(this->position, this->size);
			AABB p = AABB::FromPositionSize(player->position, player->size);

			float overlapX = glm::min((p._max.x - b._min.x), (b._max.x - p._min.x));
			float overlapY = glm::min((p._max.y - b._min.y), (b._max.y - p._min.y));
			
			if (overlapX < overlapY) 
			{
				if (player->position.x < this->position.x)
				{
					player->position.x -= overlapX;
				}
				else
				{
					player->position.x += overlapX;
				}
			}
			else 
			{
				player->SetIsGrounded();
				player->SetIsJumping();
				if (player->position.y < this->position.y)
				{
					player->position.y -= overlapY;
				}
				else
				{
					player->position.y += overlapY;
				}
			}
		}
	}
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
