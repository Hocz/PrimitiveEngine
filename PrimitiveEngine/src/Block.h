#pragma once

#include "Actor.h"

//enum class Block_Type
//{
//	
//};

class Block : public Actor
{
public:

	Block(glm::vec2 position);

	void Render() override;

	void Hit(int damage) override;
};