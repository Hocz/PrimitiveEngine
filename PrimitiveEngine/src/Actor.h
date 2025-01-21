#pragma once

#include "AABB.h"
#include <vector>

enum class ECollision_Type
{
	None,
	Everything,
	Player,
	Enemy,
	Block,
	Item,
};

class Actor {

public:
	Actor(glm::vec2 position, glm::vec2 size) 
		: position(position), size(size) { }

	virtual ~Actor() { }

	virtual void Update() {}
	virtual void Render();

	virtual void Hit(int damage) { Destroy(); }

	void Destroy() { isDestroyed = true; }
	bool GetIsDestroyed() { return isDestroyed; }

	glm::vec2 position;
	glm::vec2 size = glm::vec2(32);

	ECollision_Type collisionType = ECollision_Type::None;


	virtual bool IsColliding(const AABB& a, const AABB& b, glm::vec2& outOverlap) { return false; }
	virtual void ResolveCollision(Actor* actor, const AABB& other) { }

	virtual bool IsGrounded(const AABB& actor, const std::vector<AABB>& collidingActors, float extendedAmount) { return false; }

	virtual void SetIsGrounded(bool state) { isGrounded = state; }
	virtual void SetVelocity(float value) { }

protected:

	bool isDestroyed = false;

	bool isGrounded = false;
};