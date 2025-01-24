#include "Game.h"
#include "Player.h"
#include "Camera.h"
#include "glm.hpp"
#include "InputManager.h"
#include "WorldGenerator.h"
#include "AABB.h"

SDL_Texture* playerTex;
SDL_Rect srcR, destR;


static float deltaTime = 0.f;
static unsigned int frameCount = 0;


// time
static LARGE_INTEGER clockFrequency;
static LARGE_INTEGER lastFrameTime;
static LARGE_INTEGER startupTime;


Game::Game()
{
    worldGenerator = new WorldGenerator();
    
    inputManager = new InputManager();

    actors[0] = new Player(glm::vec2(16, -32));
    player = actors[0];


    camera = new Camera();
}

Game::~Game() // DELETE POINTERS
{
    delete inputManager;

    delete player;

    delete camera;
}

void Game::Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        // initialize window
        window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
        if (window)
        {
            std::cout << "Window created!" << std::endl;
        }


        // initialize renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            std::cout << "Renderer Created!" << std::endl;
        }


        // initialize clock for delta time calc
        QueryPerformanceFrequency(&clockFrequency);
        QueryPerformanceCounter(&startupTime);
        lastFrameTime = startupTime;

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }
}

void Game::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    
    switch (event.type)
    {
        case SDL_QUIT:
        {
            isRunning = false;
            break;
        }
    }
    
    inputManager->HandleEvents(event);
}

void Game::Update()
{
    LARGE_INTEGER currentFrameTime;
    QueryPerformanceCounter(&currentFrameTime);
    deltaTime = float(currentFrameTime.QuadPart - lastFrameTime.QuadPart) / clockFrequency.QuadPart;

    lastFrameTime = currentFrameTime;

    destR.h = 32;
    destR.w = 32;

    if (player != nullptr)
    {
        player->Update();
    }

    for (int x = 0; x < worldGenerator->WORLD_WIDTH; x++)
    {
        for (int y = 0; y < worldGenerator->WORLD_HEIGHT; y++)
        {
            Block* block = worldGenerator->worldGrid[x][y];

            if (block != nullptr)
            {
                block->Update();
            }
        }
    }


    camera->Update();

    // last thing in update
    frameCount++;
}

void Game::Render()
{
    // clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // background grid
    for (int x = -50; x <= 50; x++)
    {
        for (int y = -50; y <= 50; y++)
        {
            if ((x + y) % 2 == 0)
            {
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
            }

            glm::vec2 position = glm::vec2(x * BACKGROUND_GRID_SIZE, y * BACKGROUND_GRID_SIZE);
            position = camera->WorldToScreen(position);

            SDL_Rect rect = { position.x, position.y, BACKGROUND_GRID_SIZE, BACKGROUND_GRID_SIZE };
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    if (player != nullptr)
    {
        player->Render();
        FillRenderRect(16, -32, 10, 10);
    }

    if (worldGenerator->worldGrid != nullptr)
    {
        for (int x = 0; x < worldGenerator->WORLD_WIDTH; x++)
        {
            for (int y = 0; y < worldGenerator->WORLD_HEIGHT; y++)
            {
                if (worldGenerator->worldGrid[x][y] != nullptr)
                {
                    worldGenerator->worldGrid[x][y]->Render();
                }
            }
        }
    }

    //SDL_RenderCopy(renderer, playerTex, NULL, &destR);

    SDL_RenderPresent(renderer);
}

void Game::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}


void Game::SetRenderColor()
{
    // white color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Game::FillRenderRect(int x, int y, int width, int height)
{
    SDL_Rect rect = { x, y, width, height };
    SDL_RenderFillRect(renderer, &rect);
}

void Game::RenderRect(int x, int y, int width, int height)
{
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
    SDL_Rect rect = { x, y, width, height };
    SDL_RenderDrawRect(renderer, &rect);
}

Actor* Game::GetCollidingActor(Actor* actor, ECollision_Type collisionType)
{
    for (int i = 0; i < max_Actors; i++)
    {
        if (actors[i] == actor)
            continue;

        if (actors[i] == nullptr)
            continue;

        if (actors[i]->collisionType != collisionType)
            continue;

        AABB a = AABB::FromPositionSize(actor->position, actor->size);
        AABB b = AABB::FromPositionSize(actors[i]->position, actors[i]->size);

        if (aabbOverlap(a, b))
        {
            return actors[i];
        }
    }
    
    return nullptr;
}

std::vector<Actor*> Game::GetAllCollidingActors(Actor* actor, ECollision_Type collisionType)
{
    std::vector<Actor*> collidingActors;
    collidingActors.clear();

    if (worldGenerator->worldGrid != nullptr)
    {
        for (int x = 0; x < worldGenerator->WORLD_WIDTH; x++)
        {
            for (int y = 0; y < worldGenerator->WORLD_HEIGHT; y++)
            {
                Block* block = worldGenerator->worldGrid[x][y];

                if (block == nullptr)
                    continue;

                if (block->collisionType != collisionType)
                    continue;

                AABB a = AABB::FromPositionSize(actor->position, actor->size);
                AABB b = AABB::FromPositionSize(block->position, block->size);

                if (aabbOverlap(a, b))
                {
                    collidingActors.push_back(block);
                }
            }
        }
    }

    return collidingActors;
}


Actor* Game::GetPlayer()
{
    return player;
}

Camera* Game::GetCamera()
{
    return camera;
}

InputManager* Game::GetInputManager()
{
    return inputManager;
}

WorldGenerator* Game::GetWorldGenerator()
{
    return worldGenerator;
}


float Get_DeltaTime()
{
    return deltaTime;
}

float Get_CurrentTime()
{
    return float(lastFrameTime.QuadPart - startupTime.QuadPart) / clockFrequency.QuadPart;
}

float Get_TimePassedSince(float time)
{
    return Get_CurrentTime() - time;
}

int GetFrameCount()
{
    return frameCount;
}