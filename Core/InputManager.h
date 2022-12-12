#pragma once

#ifndef __InputManager_H__
#define __InputManager_H__

#include "SDL_mouse.h"

enum MOUSE_BUTTON { LEFT = 0, RIGHT, MIDDLE, BACK, FORWARD };

//========================================================================
class InputManager
{
private:

	static InputManager* _instance;

	InputManager();
	~InputManager();
	
protected:

	struct KeyState
	{
		bool Pressed;
		bool Released;
		bool Held;
	} m_Keys[256], m_Mouse[5];

	int m_MousePosX;
	int m_MousePosY;
	bool m_MouseMove;

	short m_KeyOldState[256] = { 0 };
	short m_KeyNewState[256] = { 0 };
	bool m_MouseOldState[5] = { 0 };
	bool m_MouseNewState[5] = { 0 };

public:
	static InputManager* GetInstance();

	void Release();

	void Update();
	void HandleKeyboard();
	void HandleMouse();

	KeyState GetKey(int KeyID) { return m_Keys[KeyID]; }
	KeyState GetMouse(MOUSE_BUTTON MouseButtonID) { return m_Mouse[MouseButtonID]; }

	bool KeyButtonDown(int KeyID) { return m_Keys[KeyID].Held; }
	bool KeyButtonPressed(int KeyID) { return m_Keys[KeyID].Pressed; }
	bool KeyButtonReleased(int KeyID) { return m_Keys[KeyID].Released; }

	bool MouseButtonDown(MOUSE_BUTTON MouseButtonID) { return m_Mouse[MouseButtonID].Held; }
	bool MouseButtonPressed(MOUSE_BUTTON MouseButtonID) { return m_Mouse[MouseButtonID].Pressed; }
	bool MouseButtonReleased(MOUSE_BUTTON MouseButtonID) { return m_Mouse[MouseButtonID].Released; }
	bool MouseMove() { return m_MouseMove; }

	int GetMouseX() { SDL_GetMouseState(&m_MousePosX, &m_MousePosY); return m_MousePosX; }
	int GetMouseY() { SDL_GetMouseState(&m_MousePosX, &m_MousePosY); return m_MousePosY; }

	char KeyStatus[512][300];
	char MouseStatus[5][300];
	//Vector2D MousePos() { return Vector2D((float)m_MousePosX, (float)m_MousePosY); }
};
#endif