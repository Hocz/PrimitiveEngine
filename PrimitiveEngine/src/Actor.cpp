#include "Actor.h"
#include "Game.h"
#include "Camera.h"

void Actor::Render()
{
	glm::vec2 renderPosition = position - size * 0.5f;
	renderPosition = game->GetCamera()->WorldToScreen(renderPosition);

	game->SetRenderColor();
	game->FillRenderRect(renderPosition.x, renderPosition.y, size.x, size.y);
}


void Actor::SetIsJumping()
{
	isJumping = false;
}

void Actor::SetIsGrounded()
{
	isGrounded = true;
}
