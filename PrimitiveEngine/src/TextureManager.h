#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <unordered_map>

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

	//SDL_Texture* LoadTexture(const char* textureName, SDL_Renderer* renderer);

	bool Load(const std::string& id, const std::string fileName, SDL_Renderer* renderer);
	void Render(const std::string& id, int x, int y, int width, int height, SDL_Renderer* renderer, float zoom);
	void Clean();

private:

	TextureManager() { }

	std::unordered_map<std::string, SDL_Texture*> textureMap;
};