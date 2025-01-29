#include "Actor.h"
#include "Game.h"
#include "Camera.h"

void Actor::Render()
{
	glm::vec2 renderPos = position - size * 0.5f;
	renderPos = Game::Instance().GetCamera()->WorldToScreen(renderPos);

	renderPosition = renderPos;
}

