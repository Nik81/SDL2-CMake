#pragma once

#ifndef __GraphicManager_H__
#define __GraphicManager_H__

#include "SDL.h"
#include "SDL_ttf.h"

//========================================================================
class GraphicManager
{
private:

	static GraphicManager* _instance;

	GraphicManager();
	~GraphicManager();

	SDL_Surface  *m_ScreenSurface = NULL;
	SDL_Renderer *m_Renderer = NULL;

protected:

	SDL_Color m_DrawColor = { 200, 0, 0, 255 };

public:
	static GraphicManager* GetInstance();

	void Release();

	int Init(SDL_Renderer *renderer);

	void Render();
	void Clear();

	void SetDrawColor(SDL_Color color);

	SDL_Renderer* GetRenderer() { return m_Renderer; }
	
	void DrawTexture(SDL_Texture* texture, SDL_Rect* dest, SDL_Rect* source = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawTexture(SDL_Texture* texture, SDL_Rect source, SDL_Rect dest, double angle, SDL_Point origin, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawText(const char* text, int posX, int posY, TTF_Font* font, SDL_Color* color);

	void DrawPoint(int pX, int pY, SDL_Color color);
	void DrawPoint(SDL_Point point, SDL_Color color);
	
	void DrawLine(int p1X, int p1Y, int p2X, int p2Y, SDL_Color color);
	void DrawLine(SDL_Point point1, SDL_Point point2, SDL_Color color);

	void DrawRect(int p1X, int p1Y, int p2X, int p2Y, SDL_Color color);
	void DrawRect(SDL_Point point1, SDL_Point point2, SDL_Color color);

	void DrawFillRect(int p1X, int p1Y, int p2X, int p2Y, SDL_Color color);
	void DrawFillRect(SDL_Point point1, SDL_Point point2, SDL_Color color);
};
#endif