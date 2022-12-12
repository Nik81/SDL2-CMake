/*=========================================================================
Program: myApp (Base SDL2 Applications)
Module:  Core
Authors: Nicola Vanella nicola.vanella@gmail.com

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.
=========================================================================*/

#include "GraphicManager.h"
#include "SDL_ttf.h"

GraphicManager*  GraphicManager::_instance = 0;//NULL;

//------------------------------------------------------------------------
GraphicManager::GraphicManager() {}
//------------------------------------------------------------------------
GraphicManager::~GraphicManager() {}

//------------------------------------------------------------------------
GraphicManager* GraphicManager::GetInstance()
{
	if (_instance == nullptr)
		_instance = new GraphicManager();

	return _instance;
}

//------------------------------------------------------------------------
void GraphicManager::Release()
{
	_instance = nullptr;
}

//------------------------------------------------------------------------
int GraphicManager::Init(SDL_Renderer *renderer)
{
	m_Renderer = renderer;
	SDL_SetRenderDrawColor(m_Renderer, m_DrawColor.r, m_DrawColor.g, m_DrawColor.b, m_DrawColor.a);
	return 0;
}

//------------------------------------------------------------------------
void GraphicManager::Render()
{
	SDL_RenderPresent(m_Renderer);
}
//------------------------------------------------------------------------
void GraphicManager::Clear()
{
	SDL_RenderClear(m_Renderer);
}

//------------------------------------------------------------------------
void GraphicManager::SetDrawColor(SDL_Color color)
{
	m_DrawColor = color;
	SDL_SetRenderDrawColor(m_Renderer, m_DrawColor.r, m_DrawColor.g, m_DrawColor.b, m_DrawColor.a);
}

//------------------------------------------------------------------------
void GraphicManager::DrawTexture(SDL_Texture* texture, SDL_Rect *dest, SDL_Rect *source, SDL_RendererFlip flip)
{
	//SDL_RenderCopy(m_Renderer, texture, source, dest);
	SDL_RenderCopyEx(m_Renderer, texture, source, dest, NULL, NULL, flip);
}
//------------------------------------------------------------------------
void GraphicManager::DrawTexture(SDL_Texture* texture, SDL_Rect source, SDL_Rect dest, double angle, SDL_Point origin, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(m_Renderer, texture, &source, &dest, angle, &origin, flip);
}
//------------------------------------------------------------------------
void GraphicManager::DrawText(const char* text, int posX, int posY, TTF_Font *font, SDL_Color *color)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, *color);
	SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(m_Renderer, surfaceMessage);

	if (surfaceMessage && messageTexture)
	{
		SDL_Rect messageRect;
		messageRect.x = posX;
		messageRect.y = posY;
		messageRect.w = surfaceMessage->w;
		messageRect.h = surfaceMessage->h;

		SDL_RenderCopy(m_Renderer, messageTexture, NULL, &messageRect);
	}

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(messageTexture);
}

//------------------------------------------------------------------------
void GraphicManager::DrawPoint(int pX, int pY, SDL_Color color)
{
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawPoint(m_Renderer, pX, pY);
	SDL_SetRenderDrawColor(m_Renderer, m_DrawColor.r, m_DrawColor.g, m_DrawColor.b, m_DrawColor.a);
}
//------------------------------------------------------------------------
void GraphicManager::DrawPoint(SDL_Point point, SDL_Color color)
{
	DrawPoint(point.x, point.y, color);
}

//------------------------------------------------------------------------
void GraphicManager::DrawLine(int p1X, int p1Y, int p2X, int p2Y, SDL_Color color)
{
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(m_Renderer, p1X, p1Y, p2X, p2Y);
	SDL_SetRenderDrawColor(m_Renderer, m_DrawColor.r, m_DrawColor.g, m_DrawColor.b, m_DrawColor.a);
}
//------------------------------------------------------------------------
void GraphicManager::DrawLine(SDL_Point point1, SDL_Point point2, SDL_Color color)
{
	DrawLine(point1.x, point1.y, point2.x, point2.y, color);
}

//------------------------------------------------------------------------
void GraphicManager::DrawRect(int p1X, int p1Y, int p2X, int p2Y, SDL_Color color)
{
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rect = { p1X, p1Y, p2X - p1X, p2Y - p1Y };
	SDL_RenderDrawRect(m_Renderer, &rect);
	SDL_SetRenderDrawColor(m_Renderer, m_DrawColor.r, m_DrawColor.g, m_DrawColor.b, m_DrawColor.a);
}
//------------------------------------------------------------------------
void GraphicManager::DrawRect(SDL_Point point1, SDL_Point point2, SDL_Color color)
{
	DrawRect(point1.x, point1.y, point2.x, point2.y, color);
}

//------------------------------------------------------------------------
void GraphicManager::DrawFillRect(int p1X, int p1Y, int p2X, int p2Y, SDL_Color color)
{
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rect = { p1X, p1Y, p2X - p1X, p2Y - p1Y };
	SDL_RenderFillRect(m_Renderer, &rect);
	SDL_SetRenderDrawColor(m_Renderer, m_DrawColor.r, m_DrawColor.g, m_DrawColor.b, m_DrawColor.a);
}
//------------------------------------------------------------------------
void GraphicManager::DrawFillRect(SDL_Point point1, SDL_Point point2, SDL_Color color)
{
	DrawFillRect(point1.x, point1.y, point2.x, point2.y, color);
}
