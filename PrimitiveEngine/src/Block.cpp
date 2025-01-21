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
	if (game->GetPlayer() != nullptr)
	{
		Actor* player = game->GetCollidingActor(this, ECollision_Type::Player);

		if (player)
		{			
			AABB block = AABB::FromPositionSize(this->position, this->size);

			ResolveCollision(player, block);

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

bool Block::IsColliding(const AABB& a, const AABB& b, glm::vec2& outOverlap)
{
	float overlapX = glm::min(a.max.x - b.min.x, b.max.x - a.min.x);
	float overlapY = glm::min(a.max.y - b.min.y, b.max.y - a.min.y);

	if (overlapX > 0 && overlapY > 0)
	{
		outOverlap = glm::vec2(overlapX, overlapY);
		return true;
	}

	return false;
}

void Block::ResolveCollision(Actor* actor, const AABB& other)
{
	glm::vec2 overlap;

	AABB a = AABB::FromPositionSize(actor->position, actor->size);
	
	if (!IsColliding(a, other, overlap))
	{
		return;
	}

	if (overlap.x < overlap.y) // checks smallest axis overlap - x or y?
	{
		if (actor->position.x < other.min.x)
		{
			actor->position.x -= overlap.x; // adjust position left
		}
		else
		{
			actor->position.x += overlap.x; // adjust position right
		}
		// TODO: Set Actor Horizontal Velocity to 0 - (ex: velocity.x = 0)
	}
	else
	{
		if (actor->position.y < other.min.y)
		{
			actor->position.y -= overlap.y; // adjust position down
			//actor->SetIsGrounded(true); // AABB Expansion instead
		}
		else
		{
			actor->position.y += overlap.y; // adjust position up
		}
		// TODO: Set Actor Vertical Velocity to 0 - (ex: velocity.y = 0)

	}
}
