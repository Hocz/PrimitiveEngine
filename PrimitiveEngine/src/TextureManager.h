#pragma once

#include "SDL.h"
#include "SDL_image.h"

class TextureManager
{
public:

	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	static TextureManager& Instance()
	{
		static TextureManager instance;
		return instance;
	}

	SDL_Texture* LoadTexture(const char* textureName, SDL_Renderer* renderer);


private:

	TextureManager() { }
};