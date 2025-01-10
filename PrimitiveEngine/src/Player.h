#pragma once

#include "Actor.h"

class Player : public Actor
{
public:

	Player(glm::vec2 position);

	void Update() override;
	void Render() override;

	void Hit(int damage) override;

	void BreakBlockAtPos();


private:

};