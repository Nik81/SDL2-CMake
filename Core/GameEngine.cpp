/*=========================================================================
Program: myApp (Base SDL2 Applications)
Module:  Core
Authors: Nicola Vanella nicola.vanella@gmail.com

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.
=========================================================================*/

#include "GameEngine.h"
#include "GameSettings.h"
#include <stdio.h>
#include <string>

//------------------------------------------------------------------------
GameEngine::GameEngine()
{	
	m_Settings = GameSettings::GetInstance();

	m_Timer = Timer::GetInstance();
	m_Graphics = GraphicManager::GetInstance();
	m_AssetManager = AssetManager::GetInstance();
	m_AudioManager = AudioManager::GetInstance();
	m_InputManager = InputManager::GetInstance();

	m_IsRunning = true;
}
//------------------------------------------------------------------------
GameEngine::~GameEngine() 
{	
	m_Settings->Release();
	m_Settings = nullptr;

	m_Timer->Release();
	m_Timer = nullptr;

	m_Graphics->Release();
	m_Graphics = nullptr;

	m_AssetManager->Release();
	m_AssetManager = nullptr;

	m_AudioManager->Release();
	m_AudioManager = nullptr;

	m_InputManager->Release();
	m_InputManager = nullptr;
}

//------------------------------------------------------------------------
int GameEngine::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0)
	{
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return 0;
	}

	Uint32 win_flags = m_Settings->FullScreen ? SDL_WINDOW_FULLSCREEN : 0;

	char title[256]; 
	sprintf_s(title, "%s - Ver %s [%d, %d]", m_Settings->WinTitle, APP_VER, m_Settings->ScreenWidth, m_Settings->ScreenHeight);
	m_WinTitle.assign(title);

	m_Window = SDL_CreateWindow(title,
		m_Settings->ScreenPosX, m_Settings->ScreenPosY,
		m_Settings->ScreenWidth, m_Settings->ScreenHeight,
		win_flags);

	if (m_Window == NULL)
	{
		printf("Could not create window: %s\n", SDL_GetError());
		return 0;
	}

	// 	screenSurface = SDL_GetWindowSurface(window);
	// 	if (screenSurface == NULL)
	// 	{
	// 		fprintf(stderr, "could not get window: %s\n", SDL_GetError());
	// 	}

	//////////////////////////////////////////////////////////////////////////
	// triggers the program that controls
	// your graphics hardware and sets flags
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	// creates a renderer to render our images
	SDL_Renderer* rend = SDL_CreateRenderer(m_Window, -1, render_flags);

	if (m_Graphics->Init(rend) != 0)
	{
		printf("Error initializing GraphicManager\n");
	}

	// Init SDL_TTF
	if (TTF_Init() != 0)
	{
		SDL_Log("Error initializing SDL_ttf");
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	// Create user resources as part of this thread
	OnUserCreate();

	// Get Screen Resolution (Test)
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	SDL_GetDesktopDisplayMode(0, &DM);
	auto Width = DM.w;
	auto Height = DM.h;

	return 1;
}
//------------------------------------------------------------------------
void GameEngine::Run() // GameLoop
{
	m_Timer->Start();

	while (m_IsRunning)
	{
		Update();
		Render();

		// Calculates to 60 fps
		SDL_Delay(1000 / 60);

		float time = 1.0f / m_Timer->ElapsedTime();
		char title[256];
		sprintf_s(title, "%s - FPS: %3.2f", m_WinTitle.c_str(), time);
		SetWindowTitle(title);
	}

	OnUserDestroy();

	Close();
}
//------------------------------------------------------------------------
void GameEngine::Close()
{
	// Destroy renderer
	SDL_DestroyRenderer(Graphics()->GetRenderer());

	// Destroy window
	SDL_DestroyWindow(m_Window);

	TTF_Quit();
	
	Mix_Quit();

	//IMG_Quit();

	// Close SDL
	SDL_Quit();
}

//------------------------------------------------------------------------
void GameEngine::Update()
{
	//m_InputManager->Update();

	// Handle Frame Update
	OnUserUpdate(m_Timer->ElapsedTime());
}
//------------------------------------------------------------------------
void GameEngine::Render()
{
	//m_Graphics->Clear();

	m_Graphics->Render();
}

/// EXTRA
//------------------------------------------------------------------------
void GameEngine::SaveSnapshot(const char* file)
{
	SDL_Surface* winSurface = SDL_GetWindowSurface(m_Window);
	SDL_Texture* winTexture = SDL_CreateTextureFromSurface(m_Graphics->GetRenderer(), winSurface);
	m_AssetManager->SaveTexture(winTexture, file);
	SDL_FreeSurface(winSurface);
	SDL_DestroyTexture(winTexture);
}