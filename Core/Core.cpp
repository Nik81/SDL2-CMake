/*=========================================================================
Program: myApp (Base SDL2 Applications)
Module:  Core
Authors: Nicola Vanella nicola.vanella@gmail.com

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.
=========================================================================*/

#include "Core.h"
#include <SDL.h>
#include <SDL_image.h>

//------------------------------------------------------------------------
Core::Core()
{
	m_Value = 1;
	m_Renderer = NULL;
}
//------------------------------------------------------------------------
Core::~Core()
{

}

//------------------------------------------------------------------------
SDL_Texture* Core::LoadTexture(const char* file)
{
	if (m_Renderer)
	{
		// creates a surface to load an image into the main memory
		SDL_Surface* surface;

		surface = IMG_Load(file);
		//surface = SDL_LoadBMP(imageFile.c_str());

		// loads image to our graphics hardware memory.
		SDL_Texture* tex = SDL_CreateTextureFromSurface(m_Renderer, surface);

		// clears main-memory
		SDL_FreeSurface(surface);

		return tex;
	}

	return NULL;
}
