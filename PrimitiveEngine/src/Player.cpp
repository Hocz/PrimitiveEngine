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
	glm::vec2 input = glm::vec2(0);

	if (game->GetInputManager()->KeyDown(Key::W))
		input.y -= 1.f;
	if (game->GetInputManager()->KeyDown(Key::S))
		input.y += 1.f;
	if (game->GetInputManager()->KeyDown(Key::D))
		input.x += 1.f;
	if (game->GetInputManager()->KeyDown(Key::A))
		input.x -= 1.f;

	glm::normalize(input);
	position += input * 250.f * Get_DeltaTime();


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
