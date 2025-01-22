#include "Player.h"
#include "Game.h"
#include "glm.hpp"
#include "InputManager.h"
#include "Camera.h"
#include "WorldGenerator.h"

Player::Player(glm::vec2 position)
	: Actor(position, glm::vec2(16))
{
	collisionType = ECollision_Type::Player;
}

void Player::Update()
{
	Player::HandleMovement();
	//Player::HandleGravity();
	//Player::HandleJump();

	if (game->GetInputManager()->MouseButtonPressed(MouseButton::Left))
	{
		BreakBlockAtPos();
	}

}

void Player::Render()
{
	Actor::Render();
}

void Player::Hit(int damage)
{
	// health check

	Destroy();
}

void Player::HandleMovement()
{
	glm::vec2 input = glm::vec2(0);

	if (game->GetInputManager()->KeyDown(Key::W)) // Up
	{
		input.y = -movementSpeed;
	}
	if (game->GetInputManager()->KeyDown(Key::S)) // Down
	{
		input.y = movementSpeed;
	}

	if (game->GetInputManager()->KeyDown(Key::D)) // Right
	{
		input.x = movementSpeed;
	}
	if (game->GetInputManager()->KeyDown(Key::A)) // Left
	{
		input.x = -movementSpeed;
	}

	glm::normalize(input);

	movementDirection.x = input.x;
	movementDirection.y = input.y;

	position += movementDirection * Get_DeltaTime();
}

void Player::HandleGravity()
{
	std::vector<Actor*> collidingActors = game->GetAllCollidingActors(this, ECollision_Type::Block);
	std::vector<AABB> actorsAABB;

	AABB player = AABB::FromPositionSize(this->position, this->size);

	for (Actor* a : collidingActors)
	{
		actorsAABB.push_back(AABB::FromPositionSize(a->position, a->size));
	}

	if (!IsGrounded(player, actorsAABB, 0.1f))
	{
		// apply gravity over time
	}
	else
	{
		// velocity.y = 0; - stop falling
	}

	/*if (isGrounded && velocity < 0.0f)
	{ 
		velocity = 10.0f;
	}
	else
	{
		velocity += gravity * Get_DeltaTime();
		std::cout << "Falling!" << std::endl;
	}

	movementDirection.y = velocity;*/
}

void Player::HandleJump()
{
	// OLD CODE
	/*if (game->GetInputManager()->KeyPressed(Key::Space) && isGrounded)
	{
		velocity -= jumpStrength;
		
		isGrounded = false;

		std::cout << "Jumping!" << std::endl;
	}

	movementDirection.y = velocity;*/
}

bool Player::IsGrounded(const AABB& actor, const std::vector<AABB>& collidingActors, float extendedAmount = 0.1f)
{
	// extends collision detection to below actor
	AABB extendedActor = actor;
	extendedActor.min.y -= extendedAmount;
	extendedActor.max.y = actor.min.y;
	
	for (const auto& a : collidingActors)
	{
		if (aabbOverlap(extendedActor, a))
		{
			return true;
		}
	}
	return false;
}

void Player::BreakBlockAtPos()
{
	int mousePosX = game->GetInputManager()->MouseX();
	int mousePosY = game->GetInputManager()->MouseY();

	glm::vec2 worldMousePos = game->GetCamera()->ScreenToWorld(glm::vec2(mousePosX, mousePosY));

	glm::vec2 blockSize(16);

	glm::vec2 gridPos = glm::floor(worldMousePos / blockSize);

	std::cout << "Mouse is over grid cell: " << (int)gridPos.x << ", " << (int)gridPos.y << std::endl;

	int gridWidth = game->GetWorldGenerator()->WORLD_WIDTH;
	int gridHeight = game->GetWorldGenerator()->WORLD_HEIGHT;

	if (gridPos.x >= 0 && gridPos.x <= gridWidth && gridPos.y >= 0 && gridPos.y <= gridHeight)
	{
		if (game->GetWorldGenerator()->worldGrid[(int)gridPos.x][(int)gridPos.y] != nullptr)
		{
			if (!game->GetWorldGenerator()->worldGrid[(int)gridPos.x][(int)gridPos.y]->GetIsDestroyed())
			{
				game->GetWorldGenerator()->worldGrid[(int)gridPos.x][(int)gridPos.y]->Destroy();
				game->GetWorldGenerator()->DestoryBlockAtPos((int)gridPos.x, (int)gridPos.y);
			}
		}
	}

}

