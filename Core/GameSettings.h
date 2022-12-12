#pragma once

#ifndef __GameSettings_H__
#define __GameSettings_H__

#include "SDL.h"
#include "appDefines.h"
#include <map>

//========================================================================
struct Resolution
{
	const char* Name;
	int ScreenWidth ;
	int ScreenHeight;
};

//========================================================================
class GameSettings
{
private:

	static GameSettings* _instance;

	GameSettings(){}
	~GameSettings() {}

	//std::vector<Resolution> Resolutions;
	/*static*/ std::map<std::string, Resolution> Resolutions;

	enum Screen_Resolution
	{
		_640x480,
		_800x600,
		_1024x768,
		_1152x864,
		_1280x600,
		_1280x720,
		_1280x768,
		_1280x800,
		_1280x960,
		_1280x1024,
		_1360X768,
		_1363X768,
		_1400X1050,
		_1440x900,
		_1600x900,
		_1680x1050,
		_1920x1080,
		_2560x1440,
		_3840x2160,
		_7680x4320,
	};

public:

	static GameSettings* GetInstance();

	void Release();

	const char* AppName = APP_NAME;
	const char* WinTitle = APP_NAME;

	bool FullScreen = false;
	int ScreenPosX = SDL_WINDOWPOS_UNDEFINED;
	int ScreenPosY = SDL_WINDOWPOS_UNDEFINED;
	int ScreenWidth = 640;
	int ScreenHeight = 480;

	bool AudioOn = true;
	int VolumeFX = 100;
	int VolumeMusic = 100;
	int VolumeVoices = 100;

	bool SubTitlesOn = true;

	int Load();
	int Load(const char* file);

	int Save();
	int Save(const char* file);

	void Print();
};
#endif