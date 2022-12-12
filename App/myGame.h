
#pragma once

#ifndef __myGame_H__
#define __myGame_H__

#include "GameEngine.h"
#include "GameEntity.h"

class myGame : public GameEngine
{
public:
	myGame();
	~myGame();

	virtual	bool OnUserCreate();
	virtual	bool OnUserUpdate(float elapsedTime);
	virtual bool OnUserDestroy();

protected:

	void UpdateInput_Debug();
	void UpdateInput2_Debug();
	void Draw();

	void DrawInputStatus_Debug();
	void DrawAudioStatus_Debug();

	SDL_Texture* m_Texture;
	SDL_Rect m_Dest;
	int m_Speed = 300;

	SDL_Texture* m_Cross;
	SDL_Rect m_CrossDest;

	TTF_Font *m_Font;

	Mix_Chunk *m_Sound;
	Mix_Music *m_Music;

	GameEntity *root;
	GameEntity *child1;
	GameEntity *child2;
	GameEntity *child3;

	float m_Rot = 0.0f;

private:
};
#endif