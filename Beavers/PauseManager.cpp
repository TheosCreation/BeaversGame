#include "PauseManager.h"
#include "Game.h"
#include "Scene.h"

PauseManager& PauseManager::GetInstance()
{
	return m_instance;
}

/*
	Initializes the pause manager instance

	@author Theo Morris
	@param Game*: pointer to the current game running
*/
void PauseManager::Init(Game* _gameRef)
{
	m_gameReference = _gameRef;
}

/*
	Toggles the pause status

	@author Theo Morris
*/
void PauseManager::TogglePaused()
{
	m_bIsPaused = !m_bIsPaused;
	UpdatePauseState();
}

/*
	Sets the pause status

	@author Theo Morris
	@param bool: pause status
*/
void PauseManager::SetPaused(bool _bIsPaused)
{
	m_bIsPaused = _bIsPaused;
	UpdatePauseState();
}

/*
	Updates the pause state

	@author Theo Morris
*/
void PauseManager::UpdatePauseState()
{
	if (m_bIsPaused)
	{
		Debug::Log("Time scale 0");
		m_gameReference->SetTimeScale(0.0f);
		m_gameReference->GetCurrentScene()->SetPauseMenu(true);
	}
	else
	{
		Debug::Log("Time scale 1");
		m_gameReference->SetTimeScale(1.0f);
		m_gameReference->GetCurrentScene()->SetPauseMenu(false);
	}
}
