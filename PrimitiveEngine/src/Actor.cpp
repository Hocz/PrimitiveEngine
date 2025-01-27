#include "Actor.h"
#include "Game.h"
#include "Camera.h"

void Actor::Render()
{
	glm::vec2 renderPosition = position - size * 0.5f;
	renderPosition = Game::Instance().GetCamera()->WorldToScreen(renderPosition);

	Game::Instance().SetRenderColor();
	Game::Instance().FillRenderRect(renderPosition.x, renderPosition.y, size.x, size.y);
}

