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
	Player::HandleGravity();
	Player::HandleJump();

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
	if (isGrounded && velocity < 0.0f)
	{ 
		velocity = 10.0f;
	}
	else
	{
		velocity += gravity * Get_DeltaTime();
		std::cout << "Falling!" << std::endl;
	}

	movementDirection.y = velocity;
}

void Player::HandleJump()
{
	if (game->GetInputManager()->KeyPressed(Key::Space) && isGrounded)
	{
		velocity -= jumpStrength;
		
		isGrounded = false;
		isJumping = true;

		std::cout << "Jumping!" << std::endl;
	}

	movementDirection.y = velocity;
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

