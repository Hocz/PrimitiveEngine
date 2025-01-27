#include "Camera.h"
#include "Config.h"
#include "Game.h"
#include "Actor.h"
#include "InputManager.h"

void Camera::Update()
{
	if (Game::Instance().GetPlayer() != nullptr)
	{
		glm::vec2 playerPosition = Game::Instance().GetPlayer()->position;
		glm::vec2 mousePosition = ScreenToWorld(glm::vec2(InputManager::Instance().MouseX(), InputManager::Instance().MouseY()));

		glm::vec2 targetPosition = glm::mix(playerPosition, mousePosition, 0.0f);

		position = glm::mix(position, targetPosition, CAMERASPEED * Get_DeltaTime());
	}
}

glm::vec2 Camera::WorldToScreen(glm::vec2 vector)
{
	using namespace Config;
	return vector - position + glm::vec2(WINDOWWIDTH * 0.5f, WINDOWHEIGHT * 0.5f);
}

glm::vec2 Camera::ScreenToWorld(glm::vec2 vector)
{
	using namespace Config;
	return vector + position - glm::vec2(WINDOWWIDTH * 0.5f, WINDOWHEIGHT * 0.5f);
}
