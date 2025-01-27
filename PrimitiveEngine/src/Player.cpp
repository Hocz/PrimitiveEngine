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
	Player::HandleMovement();
	Player::HandleGravity();
	Player::HandleJump();

	if (InputManager::Instance().MouseButtonPressed(MouseButton::Left))
	{
		BreakBlockAtPos();
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

	//std::cout << collidingActors.size() << std::endl;

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

void Player::BreakBlockAtPos()
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
		if (Game::Instance().GetWorldGenerator()->worldGrid[(int)gridPos.x][(int)gridPos.y] != nullptr)
		{
			if (!Game::Instance().GetWorldGenerator()->worldGrid[(int)gridPos.x][(int)gridPos.y]->GetIsDestroyed())
			{
				Game::Instance().GetWorldGenerator()->worldGrid[(int)gridPos.x][(int)gridPos.y]->Destroy();
				Game::Instance().GetWorldGenerator()->DestoryBlockAtPos((int)gridPos.x, (int)gridPos.y);
			}
		}
	}

}

