/*=========================================================================
Program: myApp (Base SDL2 Applications)
Module:  Core
Authors: Nicola Vanella nicola.vanella@gmail.com

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.
=========================================================================*/

#include "Game.h"

//------------------------------------------------------------------------
Game::Game()
{

}
//------------------------------------------------------------------------
Game::~Game()
{

}

//------------------------------------------------------------------------
bool Game::OnUserCreate()
{
	return true;
}
//------------------------------------------------------------------------
bool Game::OnUserUpdate(float elapsedTime)
{
	return true;
}
//------------------------------------------------------------------------
bool Game::OnUserDestroy()
{
	return true;
}
