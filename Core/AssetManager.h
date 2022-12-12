#pragma once

#ifndef __AssetManager_H__
#define __AssetManager_H__

#include "GraphicManager.h"
#include <map>
#include <SDL_ttf.h>

//========================================================================
class AssetManager
{
private:

	static AssetManager* _instance;

	AssetManager();
	~AssetManager();

	GraphicManager *m_Graphics;

	std::string m_ResourcesPath;
	std::string m_TexturePath;
	std::string m_SpritePath;
	std::string m_FontPath;

public:
	static AssetManager* GetInstance();

	void Release();

	/*static*/ std::map<std::string, SDL_Texture*> TextureMap;

	SDL_Texture* LoadTexture(const char* file);
	void SaveTexture(SDL_Texture* texture, const char* file);
	void AddTexture(std::string id, const char* file);
	void RemTexture(std::string id);
	void CleanTextures();
	SDL_Texture* GetTexture(std::string id);

	/*static*/ std::map<std::string, TTF_Font*> FontMap;

	TTF_Font* LoadFont(const char* path, int fontSize);
	void AddFont(std::string id, const char* file, int fontSize);
	void RemFont(std::string id);
	void CleanFonts();
	TTF_Font* GetFont(std::string id);

	void Print();
};
#endif