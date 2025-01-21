#pragma once

#include "glm.hpp"

struct AABB
{
	static AABB FromPositionSize(glm::vec2 position, glm::vec2 size);

	AABB() { }
	AABB(glm::vec2 in_min, glm::vec2 in_max) : min(in_min), max(in_max) { }

	glm::vec2 min;
	glm::vec2 max;
};

bool aabbOverlap(AABB a, AABB b);