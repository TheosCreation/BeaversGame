#include "BeaverGame.h"
#include "AudioManager.h"
#include "Level.h"

/*
	Event Function for Loading Menu Scene

	@author(s) Jamuel Bocacao
*/
void BeaverGame::LoadMenu()
{
	auto menu = make_shared<Scene>(Vector2u(1920, 1080), &m_window, true);
	auto optionEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadOptions);
	auto playEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadLevel);
	menu->AddImage(Vector2f(1920, 1080) / 2.0f, "Resources/Images/download.jpeg");
	menu->AddButton(Vector2f(1920, 1080) / 2.0f, "Resources/Images/Buttons/Options.png", "Resources/Audio/Click.wav", optionEvent);
	menu->AddButton(Vector2f(1920, 1080) / 2.0f + Vector2f(0.0f, -150.0f), "Resources/Images/Buttons/Play.png", "Resources/Audio/Click.wav", playEvent);

	AudioManager::GetInstance().PlayMusic("Resources/Music/Menu Music.ogg", sf::seconds(2.05f));

	SetScene(menu);
}

/*
	Event Function for Loading Options Scene

	@author(s) Jamuel Bocacao
*/
void BeaverGame::LoadOptions()
{
	auto options = make_shared<Scene>(Vector2u(1920, 1080), &m_window, false);
	auto event = make_shared<Event<void, void>>((Game*)this, &Game::LoadPreviousScene);
	options->AddButton(Vector2f(1920, 1080) / 2.0f, "Resources/Images/Buttons/Back.png", "Resources/Audio/Click.wav", event);
	SetScene(options);
}

/*
	Event Function for Loading Level

	@author(s) Jamuel Bocacao
*/
void BeaverGame::LoadLevel()
{
	AudioManager::GetInstance().StopAll();
	auto level = make_shared<Level>(Vector2u(640, 360), &m_window, true);

	auto obstacle = level->AddObject(Vector2f(500, 250), "Resources/Images/Objects/Obstacle.png", true);
	obstacle.lock()->AddBoxCollider(Vector2f(0.0f, 20.0f), Vector2f(128, 24));

	level->AddPlayer(Vector2f(640.0f, 360) / 2.0f);

	SetScene(level);
}

void BeaverGame::LoadCredits()
{
}
