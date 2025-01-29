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

	bool IsGrounded(const AABB& actor, const std::vector<AABB>& collidingActors, float extendedAmount) override;

	bool IsColliding(const AABB& a, const AABB& b, glm::vec2& outOverlap) override;
	void ResolveCollision(Actor* actor, const std::vector<AABB>& collidingActors) override;

	void Use(int i);

private:

	glm::vec2 movementDirection = glm::vec2(0);
	

	float movementSpeed = 150.0f;
	float maxMovementSpeeed = 200.0f;

	float jumpStrength = 200.0f;
	float jumpHeight = 1.0f;
	float jumpTime = 0;
	float startJump = 0;
	float jumpDuration = 0.2f;
	

	float gravity = 500.0f;

	bool isGrounded = false;

};