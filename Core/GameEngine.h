#pragma once

#ifndef __GameEngine_H__
#define __GameEngine_H__

#include "AssetManager.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "GraphicManager.h"
#include "GameSettings.h"
#include "Timer.h"
#include "SDL.h"
#include <SDL_ttf.h>

//========================================================================
class GameEngine
{
public:

	GameEngine();
	~GameEngine();

	int Init();
	void Run();

	// User MUST OVERRIDE THESE!!
	virtual bool OnUserCreate() = 0;
	virtual bool OnUserUpdate(float fElapsedTime) = 0;

	// Optional for clean up 
	virtual bool OnUserDestroy() { return true; }

	SDL_Window* GetWindow() { return m_Window; }

	void SetWindowTitle(const char* title) { SDL_SetWindowTitle(m_Window, title); }

	void SaveSnapshot(const char* file);

protected:
		
	void Update();
	void Render();

	void Exit() { m_IsRunning = false; }
	void Close();

	GameSettings* Settings() { return m_Settings; };

	AssetManager* Assets() { return m_AssetManager; };
	GraphicManager* Graphics() { return m_Graphics; };
	AudioManager* Audio() { return m_AudioManager; };
	InputManager* Input() { return m_InputManager; };

private:

	bool m_IsRunning;
	std::string m_WinTitle;

	GameSettings   *m_Settings;

	GraphicManager *m_Graphics;
	AssetManager   *m_AssetManager;
	AudioManager   *m_AudioManager;
	InputManager   *m_InputManager;
	Timer *m_Timer;

	SDL_Window *m_Window = NULL;

	// test friend
	friend class baseGame;
};
#endif