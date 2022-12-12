/*=========================================================================
Program: myApp (Base SDL2 Applications)
Module:  Core
Authors: Nicola Vanella nicola.vanella@gmail.com

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.
=========================================================================*/

#include "GameEntity.h"

//------------------------------------------------------------------------
GameEntity::GameEntity(float x /*= 0.0f*/, float y /*= 0.0f*/)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Rotation = 0.0f;
	m_IsActive = true;

	m_Parent = NULL;
}
//------------------------------------------------------------------------
GameEntity::~GameEntity()
{
	m_Parent = NULL;
}

//------------------------------------------------------------------------
void GameEntity::SetPosition(Vector2D pos)
{
	m_Position = pos;
}
//------------------------------------------------------------------------
Vector2D GameEntity::GetPosition(SPACE space)
{
	if (space == local || m_Parent == NULL)
		return m_Position;

	return m_Parent->GetPosition(world) + RotateVector(m_Position, m_Parent->GetRotation(local));
}
//------------------------------------------------------------------------
void GameEntity::SetRotation(float rotation)
{
	m_Rotation = rotation;

	if (m_Rotation > 360.0f) m_Rotation -= 360.f;
	if (m_Rotation < 360.0f) m_Rotation += 360.f;
}
//------------------------------------------------------------------------
float GameEntity::GetRotation(SPACE space)
{
	if (space == local || m_Parent == NULL)
		return m_Rotation;

	return m_Parent->GetRotation(world) + m_Rotation;
}
//------------------------------------------------------------------------
void GameEntity::SetParent(GameEntity *parent)
{
	m_Position = GetPosition(world) - parent->GetPosition(world);
	m_Parent = parent;
}

//------------------------------------------------------------------------
void GameEntity::Update()
{

}
//------------------------------------------------------------------------
void GameEntity::Render()
{

}
