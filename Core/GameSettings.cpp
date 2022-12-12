/*=========================================================================
Program: myApp (Base SDL2 Applications)
Module:  Core
Authors: Nicola Vanella nicola.vanella@gmail.com

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.
=========================================================================*/

#include "GameSettings.h"
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>

GameSettings*  GameSettings::_instance = 0;//NULL;

//------------------------------------------------------------------------
GameSettings* GameSettings::GetInstance()
{
	if (_instance == nullptr)
		_instance = new GameSettings();

	_instance->Resolutions.emplace("VGA", Resolution{ "Def HD", 640, 480 });
	_instance->Resolutions.emplace("SVGA", Resolution{ "Def HD", 800, 600 });
	_instance->Resolutions.emplace("WXGA", Resolution{ "Def HD", 1280, 720 });
	_instance->Resolutions.emplace("FHD", Resolution{ "Full HD", 1920, 1080 });
	_instance->Resolutions.emplace("QHD", Resolution{ "Quad HD", 2560, 1440 });
	_instance->Resolutions.emplace("UHD", Resolution{ "Ultra HD", 3840, 2160 });
	_instance->Resolutions.emplace("FUHD", Resolution{ "Full Ultra HD", 7680, 4320 });

	// Init Settings Test
	const char* res = "SVGA";
	_instance->FullScreen = false;
	_instance->ScreenWidth = (_instance->Resolutions[res]).ScreenWidth;
	_instance->ScreenHeight = (_instance->Resolutions[res]).ScreenHeight;

	return _instance;
}

//------------------------------------------------------------------------
void GameSettings::Release()
{
	Resolutions.clear();

	_instance = nullptr;
}

//------------------------------------------------------------------------
int GameSettings::Load()
{
	return Load("C:/DEV_64/myAppSDL3/game_Settings");
}
//------------------------------------------------------------------------
int GameSettings::Load(const char* file)
{
	//Open a file for reading
	std::ifstream load("C:/DEV_64/myAppSDL3/game_Settings");
	
	//if(load!=NULL)
	{
// 		load >> AppName;
// 		load >> " ";
// 		load >> WinTitle;
// 		load >> "\n";

		//load >> FullScreen;
		load >> ScreenPosX;
		load >> ScreenPosY;
		load >> ScreenWidth;
		load >> ScreenHeight;
	}
	
	return 0;
}

//------------------------------------------------------------------------
int GameSettings::Save()
{
	return Save("C:/DEV_64/myAppSDL3/game_Settings");
}
//------------------------------------------------------------------------
int GameSettings::Save(const char* file)
{
	//Open a file for writing
	std::ofstream save(file);

// 	save << AppName;
// 	save << " ";
// 	save << WinTitle;
// 	save << "\n";

	//save << FullScreen;
	save << ScreenPosX;
	save << ScreenPosY;
	save << ScreenWidth;
	save << ScreenHeight;

	// Close the file
	save.close();

	return 0;
}

//------------------------------------------------------------------------
void GameSettings::Print()
{
	printf("--------------------------------\n");
	printf("SETTINGS\n");
	printf("App Name: %s\n", AppName);
	printf("Win Title: %s\n", WinTitle);

	printf("\nVideo\n");
	printf(" Full screen: %d\n", FullScreen);
	printf(" Screen Position: (%d,%d)\n", ScreenPosX, ScreenPosY);
	printf(" Screen Size: (%d,%d)\n", ScreenWidth, ScreenHeight);
	
	printf("\nAudio\n");
	printf(" Audio On: %d\n", AudioOn);
	printf(" Volume FX: %d\n", VolumeFX);
	printf(" Volume Music: %d\n", VolumeMusic);
	printf(" Volume Voices: %d\n", VolumeVoices);

	printf("\nExtra\n");
	printf(" Subtitles On: %d\n", SubTitlesOn);
}
