#include "Actor.h"
#include "Game.h"
#include "Camera.h"




void Actor::Update()
{

}

void Actor::Render()
{
	glm::vec2 renderPos = position - size * 0.5f;
	renderPos = Game::Instance().GetCamera()->WorldToScreen(renderPos);

	renderPosition = renderPos;
}

void Actor::ResolveCollision(Actor* actor, float otherMass, glm::vec2 otherVelocity)
{

}

