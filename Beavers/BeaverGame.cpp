#include "BeaverGame.h"
#include "AudioManager.h"
#include "Level.h"
#include "Warehouse.h"
#include "Player.h"

/*
	Event Function for Loading Menu Scene

	@author(s) Jamuel Bocacao
*/
void BeaverGame::LoadMenu()
{
	auto menu = make_shared<Scene>(Vec2u(1920, 1080), &m_window, true);
	auto optionEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadOptions);
	auto playEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadLevel);
	menu->AddImage(Vec2f(1920, 1080) / 2.0f, "Resources/Images/download.jpeg");
	menu->AddButton(Vec2f(1920, 1080) / 2.0f, "Resources/Images/Buttons/Options.png", "Resources/Audio/Click.wav", optionEvent);
	menu->AddButton(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -150.0f), "Resources/Images/Buttons/Play.png", "Resources/Audio/Click.wav", playEvent);

	AudioManager::GetInstance().PlayMusic("Resources/Music/Menu Music.ogg", sf::seconds(2.05f));

	SetScene(menu);
}

/*
	Event Function for Loading Options Scene

	@author(s) Jamuel Bocacao
*/
void BeaverGame::LoadOptions()
{
	auto options = make_shared<Scene>(Vec2u(1920, 1080), &m_window, false);
	auto event = make_shared<Event<void, void>>((Game*)this, &Game::LoadPreviousScene);
	options->AddButton(Vec2f(1920, 1080) / 2.0f, "Resources/Images/Buttons/Back.png", "Resources/Audio/Click.wav", event);
	SetScene(options);
}

/*
	Event Function for Loading Level

	@author(s) Jamuel Bocacao and Theo Morris
*/
void BeaverGame::LoadLevel()
{
	AudioManager::GetInstance().StopAll();
	auto level = make_shared<Level>(Vec2u(640, 360), &m_window, true);

	// Creates Warehouse
	level->AddObject<Warehouse>(Vec2f(500, 250));

	// Creates a Player and adds it to the level
	auto player = make_shared<Player>(Vec2f(640, 360) / 2.0f, level->GetWorld());
	level->AddGameObject(player);

	// Adds a event to the player
	auto event = make_shared<Event<void, shared_ptr<GameObject>>>((Scene*)level.get(), &Scene::AddGameObject);
	player->SetWoodAmountChangeEvent(event);
	player->SetColor(sf::Color::Red);

	SetScene(level);
}

/*
	Event Function for Loading Credits Scene

	@author(s) Jamuel Bocacao
*/
void BeaverGame::LoadCredits()
{
}
