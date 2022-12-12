#pragma once

#ifndef __GameState_h__
#define __GameState_h__

#include <string>
#include <vector>

//========================================================================
class GameState
{
public:

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual std::string GetStateID() const = 0;
};

//========================================================================
class GameStateMachine
{
public:
	void PushState(GameState* pState)
	{
		m_GameStates.push_back(pState);
		m_GameStates.back()->onEnter();
	};

	void PopState()
	{
		if (!m_GameStates.empty())
		{
			if (m_GameStates.back()->onExit())
			{
				delete m_GameStates.back();
				m_GameStates.pop_back();
			}
		}
	};

	void ChangeState(GameState* pState)
	{
		if (!m_GameStates.empty())
		{
			if (m_GameStates.back()->GetStateID() == pState->GetStateID())
			{
				return; // do nothing
			}
			if (m_GameStates.back()->onExit())
			{
				delete m_GameStates.back();
				m_GameStates.pop_back();
			}
		}
		// push back our new state
		m_GameStates.push_back(pState);
		
		// initialize it
		m_GameStates.back()->onEnter();
	};

	void GameStateMachine::Update()
	{
		if (!m_GameStates.empty())
		{
			m_GameStates.back()->Update();
		}
	};

	void GameStateMachine::Render()
	{
		if (!m_GameStates.empty())
		{
			m_GameStates.back()->Render();
		}
	};

private:

	std::vector<GameState*> m_GameStates;
};

#endif // _GameState_h_
