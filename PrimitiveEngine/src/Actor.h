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

	glm::vec2 velocity = glm::vec2(0);


	virtual bool IsColliding(const AABB& a, const AABB& b, glm::vec2& outOverlap) { return false; }
	virtual void ResolveCollision(Actor* actor, const std::vector<AABB>& collidingActors) { }

	virtual bool IsGrounded(const AABB& actor, const std::vector<AABB>& collidingActors, float extendedAmount) { return false; }

protected:

	bool isDestroyed = false;
};