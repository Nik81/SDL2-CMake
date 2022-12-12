#pragma once

#ifndef __Game_H__
#define __Game_H__

#include "GameEngine.h"

//========================================================================
class Game : public GameEngine
{
public:
	Game();
	~Game();

	virtual	bool OnUserCreate();
	virtual	bool OnUserUpdate(float elapsedTime);
	virtual bool OnUserDestroy();

protected:

private:
};
#endif