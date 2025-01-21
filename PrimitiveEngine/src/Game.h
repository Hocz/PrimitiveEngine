#pragma once

#include <iostream>
#include "SDL_image.h"
#include <SDL.h>
#include <vector>

#define NOMINMAX
#include <windows.h>

static constexpr int max_Actors = 50;

// Forward declarations
class Actor;
enum class ECollision_Type;
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

	Actor* GetCollidingActor(Actor* other, ECollision_Type collisionType);
	std::vector<Actor*> GetAllCollidingActors(Actor* other, ECollision_Type collisionType);

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

	Actor* actors[max_Actors] = { nullptr };


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
