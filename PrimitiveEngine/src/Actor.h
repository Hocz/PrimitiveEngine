#pragma once

#include "glm.hpp"

enum class ECollision_Type
{
	None,
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

	virtual void SetIsJumping();
	virtual void SetIsGrounded();

protected:

	bool isDestroyed = false;

	bool isJumping = false;
	bool isGrounded = false;
};