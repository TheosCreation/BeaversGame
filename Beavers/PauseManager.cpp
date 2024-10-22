#include "PauseManager.h"
#include "Game.h"

PauseManager& PauseManager::GetInstance()
{
	return m_instance;
}

void PauseManager::Init(Game* _gameRef)
{
	m_gameReference = _gameRef;
}

void PauseManager::TogglePaused()
{
	m_bIsPaused = !m_bIsPaused;
	if (m_bIsPaused)
	{
		Debug::Log("Time scale 0");
		m_gameReference->SetTimeScale(0.0f);
	}
	else
	{
		Debug::Log("Time scale 1");
		m_gameReference->SetTimeScale(1.0f);
	}
}
