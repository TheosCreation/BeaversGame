#pragma once
#include "Utils.h"

//Forward decleration
class Game;

class PauseManager
{
public:
	static PauseManager& GetInstance();

	void Init(Game* _gameRef);

	void TogglePaused();
	void SetPaused(bool _bIsPaused);
	void UpdatePauseState();

private:
	PauseManager() = default;
	~PauseManager() = default;

	PauseManager(const PauseManager& _copy) = delete;
	PauseManager& operator = (const PauseManager& _copy) = delete;

private:
	static PauseManager m_instance;
	bool m_bIsPaused = false;
	Game* m_gameReference = nullptr;
};

inline PauseManager PauseManager::m_instance;
