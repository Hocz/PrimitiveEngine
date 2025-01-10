#pragma once

#include <iostream>
#include "SDL_image.h"
#include <SDL.h>
#include <windows.h>


// Forward declarations
class Actor;
class Camera;
class InputManager;
class WorldGenerator;

class Game {

public:

	Game();
	~Game();

	void Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);


	void HandleEvents();

	void Update();

	void Render();


	void Clean();

	bool Running() { return isRunning; }

	void SetRenderColor();
	void FillRenderRect(int x, int y, int width, int height);

	// getter functions
	Actor* GetPlayer();
	Camera* GetCamera();
	InputManager* GetInputManager();
	WorldGenerator* GetWorldGenerator();

private:

	SDL_Window* window;
	SDL_Renderer* renderer;

	bool isRunning;

	static constexpr float BACKGROUND_GRID_SIZE = 50.f;

	WorldGenerator* worldGenerator = nullptr;

	InputManager* inputManager = nullptr;

	Actor* player = nullptr;

	Camera* camera = nullptr;

};

extern Game* game;

// game time
float Get_DeltaTime();

float Get_CurrentTime();

float Get_TimePassedSince(float time);

int GetFrameCount();
