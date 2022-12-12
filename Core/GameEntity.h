#pragma once

#ifndef __GameEntity_H__
#define __GameEntity_H__

#include "Vector2D.h"

class GameEntity
{
public:
	enum  SPACE	{ local = 0, world = 1 };

	GameEntity(float x = 0.0f, float y = 0.0f);
	~GameEntity();

	void SetPosition(Vector2D pos);
	Vector2D GetPosition(SPACE space);

	void SetRotation(float rotation);
	float GetRotation(SPACE space);

	bool IsActive() { return m_IsActive; }
	void Active(bool active) { m_IsActive = active; }

	void SetParent(GameEntity *parent);
	GameEntity* GetParent() { return m_Parent; }

	virtual void Update();
	virtual void Render();

private:

	Vector2D m_Position;
	float m_Rotation;	
	bool m_IsActive;

	GameEntity *m_Parent;
};
#endif // __GameEntity_H__
