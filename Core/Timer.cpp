/*=========================================================================
Program: myApp (Base SDL2 Applications)
Module:  Core
Authors: Nicola Vanella nicola.vanella@gmail.com

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.
=========================================================================*/

#include "Timer.h"
#include <chrono>

Timer*  Timer::_instance = 0;//NULL;

auto tp1 = std::chrono::system_clock::now();
auto tp2 = std::chrono::system_clock::now();

Timer* Timer::GetInstance()
{
	if (_instance == nullptr)
		_instance = new Timer();

	return _instance;
}

void Timer::Release()
{
	_instance = nullptr;
}

void Timer::Start()
{
	tp1 = std::chrono::system_clock::now();
	tp2 = std::chrono::system_clock::now();
}

float Timer::ElapsedTime()
{
	// Handle Timing
	tp2 = std::chrono::system_clock::now();
	std::chrono::duration<float> elapsedTime = tp2 - tp1;
	tp1 = tp2;

	return elapsedTime.count();
}

Timer::Timer()
{
}

Timer::~Timer()
{
}
