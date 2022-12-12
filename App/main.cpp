/*=========================================================================
Program: myApp (Base SDL2 Applications)
Module:  App
Authors: Nicola Vanella nicola.vanella@gmail.com

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.
=========================================================================*/

#include "myGame.h"

int main(int argc, char *argv[])
{
	myGame *game = new myGame();

	game->Init();
	game->Run();

	return 0;
}