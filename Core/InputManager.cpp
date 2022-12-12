/*=========================================================================
Program: myApp (Base SDL2 Applications)
Module:  Core
Authors: Nicola Vanella nicola.vanella@gmail.com

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.
=========================================================================*/

#include "InputManager.h"
#include "SDL_events.h"
#include <stdio.h>

InputManager*  InputManager::_instance = 0;//NULL;

//------------------------------------------------------------------------
InputManager::InputManager()
{
	m_MousePosX = 0;
	m_MousePosY = 0;
	m_MouseMove = false;
}
//------------------------------------------------------------------------
InputManager::~InputManager() {}

//------------------------------------------------------------------------
InputManager* InputManager::GetInstance()
{
	if (_instance == nullptr)
		_instance = new InputManager();

	return _instance;
}
//------------------------------------------------------------------------
void InputManager::Release()
{
	_instance = nullptr;
}

//------------------------------------------------------------------------
void InputManager::Update()
{
	m_MouseMove = false;

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			//GameEngine::IsRunning = false;
			return;
			break;

		case SDL_KEYDOWN:
		{
			int k = e.key.keysym.sym & 0xfff; // SDL Keycode
			m_KeyNewState[k] = true;

			printf("Key Down: %d %c\n", k, static_cast<char>(k));
		}
		break;

		case SDL_KEYUP:
		{
			int k = e.key.keysym.sym & 0xfff; // SDL Keycode
			m_KeyNewState[k] = false;

			printf("Key Up: %d\n", k);
		}
		break;

		case SDL_MOUSEMOTION:
		{
			m_MousePosX = e.motion.x;
			m_MousePosY = e.motion.y;
			m_MouseMove = true;

			//printf("Mouse Pos: %d, %d\n", m_MousePosX, m_MousePosY);
		}
		break;

		case SDL_MOUSEBUTTONDOWN:
		{
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				m_MouseNewState[0] = 1;
				break;
			case SDL_BUTTON_RIGHT:
				m_MouseNewState[1] = 1;
				break;
			case SDL_BUTTON_MIDDLE:
				m_MouseNewState[2] = 1;
				break;
			case SDL_BUTTON_X1:
				m_MouseNewState[3] = 1;
				break;
			case SDL_BUTTON_X2:
				m_MouseNewState[4] = 1;
				break;
			}
		}
		break;

		case SDL_MOUSEBUTTONUP:
		{
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				m_MouseNewState[0] = 0;
				break;
			case SDL_BUTTON_RIGHT:
				m_MouseNewState[1] = 0;
				break;
			case SDL_BUTTON_MIDDLE:
				m_MouseNewState[2] = 0;
				break;
			case SDL_BUTTON_X1:
				m_MouseNewState[3] = 0;
				break;
			case SDL_BUTTON_X2:
				m_MouseNewState[4] = 0;
				break;
			}
		}
		break;
		}
	}

	HandleKeyboard();
	HandleMouse();
}
//------------------------------------------------------------------------
void InputManager::HandleKeyboard()
{
	// Handle Keyboard Input - Check for window events
	for (int k = 0; k < 512; k++)
	{
		m_Keys[k].Pressed = false;
		m_Keys[k].Released = false;

		if (m_KeyNewState[k] != m_KeyOldState[k])
		{
			if (m_KeyNewState[k] == true)
			{
				m_Keys[k].Pressed = !m_Keys[k].Held;
				m_Keys[k].Held = true;
			}
			else
			{
				m_Keys[k].Released = true;
				m_Keys[k].Held = false;
			}
		}

		m_KeyOldState[k] = m_KeyNewState[k];

		sprintf(KeyStatus[k], "Key Button %d, Pressed %d, Held %d - Old %d - New %d", k, m_Keys[k].Pressed, m_Keys[k].Held, m_KeyOldState[k], m_KeyNewState[k]);
	}
}
//------------------------------------------------------------------------
void InputManager::HandleMouse()
{
	// Handle Mouse Input - Check for window events
	for (int m = 0; m < 5; m++)
	{
		m_Mouse[m].Pressed = false;
		m_Mouse[m].Released = false;

		if (m_MouseNewState[m] != m_MouseOldState[m])
		{
			if (m_MouseNewState[m])
			{
				m_Mouse[m].Pressed = true;
				m_Mouse[m].Held = true;
			}
			else
			{
				m_Mouse[m].Released = true;
				m_Mouse[m].Held = false;
			}
		}

		m_MouseOldState[m] = m_MouseNewState[m];

		sprintf(MouseStatus[m], "Mouse Button %d, Pressed %d, Held %d - Old %d - New %d", m, m_Mouse[m].Pressed, m_Mouse[m].Held, m_MouseOldState[m], m_MouseNewState[m]);
	}
}