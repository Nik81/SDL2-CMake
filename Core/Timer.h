#pragma once

#ifndef __Timer_H__
#define __Timer_H__

//========================================================================
class Timer
{
private:

	static Timer* _instance;

	Timer();
	~Timer();

public:
	static Timer* GetInstance();

	void Release();

	void Start();
	float ElapsedTime();
};
#endif
