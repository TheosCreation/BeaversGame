#pragma once
#include "Game.h"
class BeaverGame : public Game
{
public:
	BeaverGame() = default;

private:
	void LoadMenu() override;
	void LoadOptions();
	void LoadLevel();
	void LoadCredits();
};

