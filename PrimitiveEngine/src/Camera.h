#pragma once

#include "glm.hpp"

class Camera
{
public:
	void Update();

	static constexpr float CAMERASPEED = 5.f;

	glm::vec2 WorldToScreen(glm::vec2 vector);
	glm::vec2 ScreenToWorld(glm::vec2 vector);

	glm::vec2 position;
	
};