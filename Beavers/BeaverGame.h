#pragma once
#include "Game.h"
class BeaverGame : public Game
{
public:
	BeaverGame() = default;

private:
	void LoadMainMenu() override;
	void LoadOptions();
	void LoadLevel();
	void LoadCredits();
	void LoadWinGame();
	void LoadGameOver();

	void Quit();
};

