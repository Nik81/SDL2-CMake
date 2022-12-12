/*=========================================================================
Program: myApp (Base SDL2 Applications)
Module:  Core
Authors: Nicola Vanella nicola.vanella@gmail.com

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.
=========================================================================*/

#include "AssetManager.h"
#include "appDefines.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>

AssetManager*  AssetManager::_instance = 0;//NULL;

//------------------------------------------------------------------------
AssetManager::AssetManager() 
{
	m_Graphics = GraphicManager::GetInstance();

	m_ResourcesPath = APP_ASSETS_DIR;
	m_TexturePath = m_ResourcesPath + "/Images/";
	m_FontPath = m_ResourcesPath + "/Fonts/";
}
//------------------------------------------------------------------------
AssetManager::~AssetManager()
{
	m_Graphics->Release();
}

//------------------------------------------------------------------------
AssetManager* AssetManager::GetInstance()
{
	if (_instance == nullptr)
		_instance = new AssetManager();

	return _instance;
}
//------------------------------------------------------------------------
void AssetManager::Release()
{	
	CleanTextures();
	CleanFonts();

	//TextureMap.clear();
	//FontMap.clear();
	
	//delete _instance;
	_instance = nullptr;
}

/// TEXTURES
//------------------------------------------------------------------------
SDL_Texture* AssetManager::LoadTexture(const char* file)
{
	SDL_Renderer *renderer = m_Graphics->GetRenderer();

	if (renderer)
	{
		std::string imageFile = m_TexturePath + file;

		// Creates a surface to load an image into the main memory
		SDL_Surface* surface = IMG_Load(imageFile.c_str());
		
		// Loads image to our graphics hardware memory.
		SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);

		// Clears main-memory
		SDL_FreeSurface(surface);

		return tex;
	}

	return NULL;
}
//------------------------------------------------------------------------
void AssetManager::SaveTexture(SDL_Texture* texture, const char* file)
{
	SDL_Renderer *renderer = m_Graphics->GetRenderer();

	if (renderer)
	{
		SDL_Texture* target = SDL_GetRenderTarget(renderer);
		SDL_SetRenderTarget(renderer, texture);
		int width, height;
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);
		SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
		SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
		IMG_SavePNG(surface, file);
		SDL_FreeSurface(surface);
		SDL_SetRenderTarget(renderer, target);
	}
}
//------------------------------------------------------------------------
void AssetManager::AddTexture(std::string id, const char* file)
{
	SDL_Texture* texture = LoadTexture(file);

	if (texture)
		TextureMap.emplace(id, texture);
}
//------------------------------------------------------------------------
void AssetManager::RemTexture(std::string id)
{
	SDL_Texture* texture = TextureMap[id];

	if (texture)
		SDL_DestroyTexture(texture);

	TextureMap.erase(id);
}
//------------------------------------------------------------------------
SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return TextureMap[id];
}
//------------------------------------------------------------------------
void AssetManager::CleanTextures()
{
	int debug_count = 0;

	std::map<std::string, SDL_Texture*>::iterator it;
	for (it = TextureMap.begin(); it != TextureMap.end(); it++)
	{
		debug_count++;
		SDL_DestroyTexture(it->second);
	}

	TextureMap.clear();

	//SDL_Log("AssetManager: ClearTextures: Removed %d textures", debug_count);
}

/// FONTS
//------------------------------------------------------------------------
TTF_Font* AssetManager::LoadFont(const char* file, int fontSize)
{
	std::string fontFile = m_FontPath + file;

	return TTF_OpenFont(fontFile.c_str(), fontSize);
}
//------------------------------------------------------------------------
void AssetManager::AddFont(std::string id, const char* file, int fontSize)
{
	TTF_Font* font = LoadFont(file, fontSize);

	if (font)
		FontMap.emplace(id, font);
}
//------------------------------------------------------------------------
void AssetManager::RemFont(std::string id)
{
	TTF_Font* font = FontMap[id];

	if (font)
	{
		TTF_CloseFont(font);
		font = NULL;
	}

	FontMap.erase(id);
}
//------------------------------------------------------------------------
TTF_Font* AssetManager::GetFont(std::string id)
{
	return FontMap[id];
}
//------------------------------------------------------------------------
void AssetManager::CleanFonts()
{
	int debug_count = 0;

	std::map<std::string, TTF_Font*>::iterator it;
	for (it = FontMap.begin(); it != FontMap.end(); it++)
	{
		debug_count++;
		TTF_CloseFont(it->second);
	}

	FontMap.clear();

	//SDL_Log("AssetManager: ClearFonts: Removed %d fonts", debug_count);
}

//------------------------------------------------------------------------
void AssetManager::Print()
{
	printf("--------------------------------\n");
	printf("\ASSETS MANAGER\n");

	printf(" Textures: %d\n", TextureMap.size());

// 	std::map<std::string, SDL_Texture*>::iterator it;
// 	for (it = TextureMap.begin(); it != TextureMap.end(); it++)
// 	{
// 		printf(" %s\n", it->first);
// 		printf(" %s\n", it->second);
// 	}

	printf(" Fonts: %d\n", FontMap.size());
}
