#pragma once

#include "Actor.h"

class Block : public Actor
{
public:

	Block(glm::vec2 position);

	void Update() override;
	void Render() override;

	void Hit(int damage) override;
};