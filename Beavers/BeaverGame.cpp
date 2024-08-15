#include "BeaverGame.h"
#include "AudioManager.h"
#include "Level.h"

void BeaverGame::LoadMenu()
{
	auto menu = make_shared<Scene>(Vec2u(1920, 1080), &m_window, true);
	auto optionEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadOptions);
	auto playEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadLevel);
	menu->AddImage(Vec2f(1920, 1080) / 2.0f, "Resources/Images/download.jpeg");
	menu->AddButton(Vec2f(1920, 1080) / 2.0f, "Resources/Images/Buttons/Options.png", "Resources/Audio/Click.wav", optionEvent);
	menu->AddButton(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, 100.0f), "Resources/Images/Buttons/Play.png", "Resources/Audio/Click.wav", playEvent);

	AudioManager::GetInstance().PlayMusic("Resources/Music/Menu Music.ogg", sf::seconds(2.05f));

	SetScene(menu);
}

void BeaverGame::LoadOptions()
{
	auto options = make_shared<Scene>(Vec2u(1920, 1080), &m_window, false);
	auto event = make_shared<Event<void, void>>((Game*)this, &Game::LoadPreviousScene);
	options->AddButton(Vec2f(1920, 1080) / 2.0f, "Resources/Images/Buttons/Back.png", "Resources/Audio/Click.wav", event);
	SetScene(options);
}

void BeaverGame::LoadLevel()
{
	auto level = make_shared<Level>(Vec2u(640, 360), &m_window, true);
	SetScene(level);
}