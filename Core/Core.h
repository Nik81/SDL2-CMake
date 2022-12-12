#pragma once

#ifndef __Core_H__
#define __Core_H__

#include "SDL_render.h"

//========================================================================
class Core
{
public:
	Core();
	~Core();

	int GetValue() { return m_Value; };
	void SetValue(int value) { m_Value = value; };

	void SetRenderer(SDL_Renderer *renderer) { m_Renderer = renderer; };

	SDL_Texture* LoadTexture(const char* file);

protected:

	int m_Value;
	SDL_Renderer *m_Renderer;

private:
};
#endif // __Core_H__