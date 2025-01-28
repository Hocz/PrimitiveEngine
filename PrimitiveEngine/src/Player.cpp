#include "Player.h"
#include "Game.h"
#include "glm.hpp"
#include "InputManager.h"
#include "Camera.h"
#include "WorldGenerator.h"

Player::Player(glm::vec2 position)
	: Actor(position, glm::vec2(12))
{
	collisionType = ECollision_Type::Player;
}

void Player::Update()
{
	HandleMovement();
	HandleGravity();
	HandleJump();

	std::vector<Actor*> collidingActors = Game::Instance().GetAllCollidingActors(this, ECollision_Type::Block);
	std::vector<AABB> actorsAABB;

	for (Actor* a : collidingActors)
	{
		AABB aabb = AABB::FromPositionSize(a->position, a->size);
		actorsAABB.push_back(aabb);
	}
	ResolveCollision(this, actorsAABB);


	if (InputManager::Instance().MouseButtonPressed(MouseButton::Left))
	{
		Use(0);
	}

	if (InputManager::Instance().MouseButtonPressed(MouseButton::Right))
	{
		Use(1);
	}

}

void Player::Render()
{
	Actor::Render();

	glm::vec2 newPos = glm::vec2(position.x, position.y + (size.y * 0.5f));
	glm::vec2 newSize = glm::vec2(size.x * 0.75, size.y * 0.5f);

	AABB extendedActor = AABB::FromPositionSize(newPos, newSize);

	int width = extendedActor.max.x - extendedActor.min.x;
	int height = extendedActor.max.y - extendedActor.min.y;

	glm::vec2 renderPosition = newPos - glm::vec2(width, height) * 0.5f;
	renderPosition = Game::Instance().GetCamera()->WorldToScreen(renderPosition);

	Game::Instance().RenderRect(renderPosition.x, renderPosition.y, width, height);
}

void Player::Hit(int damage)
{
	// health check

	Destroy();
}

void Player::HandleMovement()
{

	if (InputManager::Instance().KeyDown(Key::D)) // Right
	{
		velocity.x += movementSpeed * Get_DeltaTime();
		velocity.x = glm::clamp(velocity.x, 0.0f, maxMovementSpeeed);
	}
	else if (InputManager::Instance().KeyDown(Key::A)) // Left
	{
		velocity.x -= movementSpeed * Get_DeltaTime();
		velocity.x = glm::clamp(velocity.x, -maxMovementSpeeed, 0.0f);
	}
	else
	{
		velocity.x = 0;
	}
	

	movementDirection.x = velocity.x;

	position += movementDirection * Get_DeltaTime();
}

void Player::HandleGravity()
{
	std::vector<Actor*> collidingActors = Game::Instance().GetAllCollidingActors(this, ECollision_Type::Block);
	std::vector<AABB> actorsAABB;

	AABB player = AABB::FromPositionSize(this->position, this->size);

	for (Actor* a : collidingActors)
	{
		AABB aabb = AABB::FromPositionSize(a->position, a->size);
		actorsAABB.push_back(aabb);
	}

	if (!IsGrounded(player, actorsAABB, 2.0f))
	{
		velocity.y += gravity * Get_DeltaTime();
	}
	else
	{
		velocity.y = 0;
		isGrounded = true;
		isJumping = false;
	}

	movementDirection.y = velocity.y;
}

void Player::HandleJump()
{	
	if (InputManager::Instance().KeyPressed(Key::Space) && isGrounded)
	{
		velocity.y -= jumpStrength;
	}

	movementDirection.y = velocity.y;
}

bool Player::IsGrounded(const AABB& actor, const std::vector<AABB>& collidingActors, float extendedAmount)
{
	glm::vec2 newPos = glm::vec2(position.x, position.y + (size.y * 0.5f));
	glm::vec2 newSize = glm::vec2(size.x * 0.75, (size.y * 0.5f));

	AABB extendedActor = AABB::FromPositionSize(newPos, newSize);

	for (const auto& a : collidingActors)
	{
		if (aabbOverlap(extendedActor, a))
		{
			isGrounded = true;
			return true;
		}
	}
	isGrounded = false;
	return false;
}

bool Player::IsColliding(const AABB& a, const AABB& b, glm::vec2& outOverlap)
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

void Player::ResolveCollision(Actor* actor, const std::vector<AABB>& collidingActors)
{
	glm::vec2 overlap;

	AABB a = AABB::FromPositionSize(actor->position, actor->size);

	for (const auto& cA : collidingActors)
	{
		if (!IsColliding(a, cA, overlap))
		{
			continue;
		}

		float overlapArea = 0.0f;

		float overlapX = glm::max(0.0f, glm::min(a.max.x, cA.max.x) - glm::max(a.min.x, cA.min.x));
		float overlapY = glm::max(0.0f, glm::min(a.max.y, cA.max.y) - glm::max(a.min.y, cA.min.y));
		overlapArea = overlapX * overlapY;

		if (overlapArea > ((actor->size.x * actor->size.y) * 0.5f))
		{
			actor->velocity = glm::vec2(0);
			return;
		}


		if (overlap.x < overlap.y) // checks smallest axis overlap - x or y?
		{
			if (actor->position.x < cA.min.x)
			{
				actor->position.x -= overlap.x; // adjust position left
			}
			else
			{
				actor->position.x += overlap.x; // adjust position right
			}
			actor->velocity.x = 0;
		}
		else
		{
			if (actor->position.y < cA.min.y)
			{
				actor->position.y -= overlap.y; // adjust position down
			}
			else
			{
				actor->position.y += overlap.y; // adjust position up
			}
			actor->velocity.y = 0;
		}
	}
}


void Player::Use(int i)
{
	int mousePosX = InputManager::Instance().MouseX();
	int mousePosY = InputManager::Instance().MouseY();

	glm::vec2 worldMousePos = Game::Instance().GetCamera()->ScreenToWorld(glm::vec2(mousePosX, mousePosY));

	glm::vec2 blockSize(16);

	glm::vec2 gridPos = glm::floor(worldMousePos / blockSize);

	std::cout << "Mouse is over grid cell: " << (int)gridPos.x << ", " << (int)gridPos.y << std::endl;

	int gridWidth = Game::Instance().GetWorldGenerator()->WORLD_WIDTH;
	int gridHeight = Game::Instance().GetWorldGenerator()->WORLD_HEIGHT;

	if (gridPos.x >= 0 && gridPos.x <= gridWidth && gridPos.y >= 0 && gridPos.y <= gridHeight)
	{
		if (i == 0) // break
		{
			Game::Instance().GetWorldGenerator()->DestoryBlockAtPos((int)gridPos.x, (int)gridPos.y);
		}
		else if (i == 1) //place
		{
			Game::Instance().GetWorldGenerator()->CreateBlockAtPos((int)gridPos.x, (int)gridPos.y);
		}
	}
}

