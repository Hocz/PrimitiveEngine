#include "TextureManager.h"
#include <iostream>

//SDL_Texture* TextureManager::LoadTexture(const char* textureName, SDL_Renderer* renderer)
//{
//	SDL_Surface* tempSurface = IMG_Load(textureName);
//	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
//	SDL_FreeSurface(tempSurface);
//
//	return texture;
//}

bool TextureManager::Load(const std::string& id, const std::string fileName, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load(fileName.c_str());
	if (!tempSurface)
	{
		std::cerr << "Failed to Load Texture! File: " << fileName << "Error: " << IMG_GetError() << std::endl;
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	if (!texture)
	{
		std::cerr << "Failed to Create Texture! File: " << fileName << "Error: " << IMG_GetError() << std::endl;
		return false;
	}

	textureMap[id] = texture;
	return true;
}

void TextureManager::Render(const std::string& id, int x, int y, int width, int height, SDL_Renderer* renderer, float zoom)
{
	width = static_cast<int>(width * zoom);
	height = static_cast<int>(height * zoom);

	SDL_Rect srcRect = { 0, 0, width, height };
	SDL_Rect destRect = { x, y, width, height };

	SDL_RenderCopy(renderer, textureMap[id], &srcRect, &destRect);
}

void TextureManager::Clean()
{
	for (auto& texturePair : textureMap)
	{
		SDL_DestroyTexture(texturePair.second);
	}
	textureMap.clear();
}
