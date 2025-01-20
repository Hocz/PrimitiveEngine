#pragma once

#include "Actor.h"

class Player : public Actor
{
public:

	Player(glm::vec2 position);

	void Update() override;
	void Render() override;

	void Hit(int damage) override;

	void HandleMovement();
	void HandleGravity();
	void HandleJump();


	void BreakBlockAtPos();


private:

	glm::vec2 movementDirection;
	

	float movementSpeed = 200.f;
	float jumpStrength = 150.f;
	float gravity = 50.f;

	float velocity;
};