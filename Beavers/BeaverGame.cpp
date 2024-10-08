#include "BeaverGame.h"
#include "AudioManager.h"
#include "Level.h"
#include "Warehouse.h"
#include "Player.h"
#include "Tree.h"
#include "Text.h"
#include "TileMap.h"
#include "Hint.h"

/*
	Event Function for Loading Menu Scene

	@author(s) Jamuel Bocacao
*/
void BeaverGame::LoadMenu()
{
	auto menu = make_shared<Scene>(Vec2u(1920, 1080), &m_window, true);
	auto optionEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadOptions);
	auto playEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadLevel);
	auto quitEvent = make_shared<Event<void, void>>(this, &BeaverGame::Quit);
	menu->AddImage(Vec2f(1920, 1080) / 2.0f, "Resources/Images/download.jpeg", -10);
	menu->AddButton(Vec2f(1920, 1080) / 2.0f, "Resources/Images/Buttons/Options.png", "Resources/Audio/Click.wav", optionEvent);
	menu->AddButton(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -150.0f), "Resources/Images/Buttons/Play.png", "Resources/Audio/Click.wav", playEvent);
	menu->AddButton(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, 150.0f), "Resources/Images/Buttons/Quit.png", "Resources/Audio/Click.wav", quitEvent);
	menu->AddText(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -300.0f), "Beaverpocalypse", 100);

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
	auto backEvent = make_shared<Event<void, void>>((Game*)this, &Game::LoadPreviousScene);
	auto soundDragEvent = make_shared<Event<void, int>>(&AudioManager::GetInstance(), &AudioManager::SetSoundVolume);
	auto musicDragEvent = make_shared<Event<void, int>>(&AudioManager::GetInstance(), &AudioManager::SetMusicVolume);
	options->AddText(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -300.0f), "Options", 100);
	options->AddSlider(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -150.0f), 50, 100, soundDragEvent);
	options->AddSlider(Vec2f(1920, 1080) / 2.0f, 50, 100, musicDragEvent);
	options->AddButton(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, 150.0f), "Resources/Images/Buttons/Back.png", "Resources/Audio/Click.wav", backEvent);

	SetScene(options);
}

/*
	Event Function for Loading Level

	@author(s) Jamuel Bocacao and Theo Morris and Kazuo Reis
*/
void BeaverGame::LoadLevel()
{

	AudioManager::GetInstance().StopAll();
	auto level = make_shared<Level>(Vec2u(640, 360), &m_window, true);

	// Creates Warehouse
	Warehouse* warehouseRef = level->AddObject<Warehouse>(Vec2f(500, 250)).lock().get();

	// Creates a Player and adds it to the level
	auto player = make_shared<Player>(Vec2f(640, 360) / 2.0f, level->GetWorld());
	
	level->AddGameObject(player);

	// Adds a event to the player
	auto event = make_shared<Event2P<void, shared_ptr<GameObject>, int>>((Scene*)level.get(), &Scene::AddGameObject);
	player->SetWoodAmountChangeEvent(event);

	level->AddObject<Tree>(Vec2f(150, 150));
	// Creates Shop(s)
	auto shop1 = make_shared<Shop>(Vec2f(90, 50), level->GetWorld(), warehouseRef, 1, "Resources/Images/Objects/AxeShop.png");
	auto shop2 = make_shared<Shop>(Vec2f(38, 50), level->GetWorld(), warehouseRef, 1, "Resources/Images/Objects/BootShop.png");
	auto shop3 = make_shared<Shop>(Vec2f(142, 50), level->GetWorld(), warehouseRef, 1, "Resources/Images/Objects/BagShop.png");

	level->AddGameObject(shop1);
	level->AddGameObject(shop2);
	level->AddGameObject(shop3);

	// Creates TileMap
	// First vector is tilemap size second is tile size
	auto tileMap = make_shared<TileMap>(Vec2u(22, 12), Vec2f(32, 32));
	level->AddGameObject(tileMap);

	// Creates different tile types
	


	// Test tiles

	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			// This can be exapanded to place as many tiles as you want in whatever patern you want
			auto grassTile = make_shared<Tile>("Resources/Images/Tiles/grass.png");
			tileMap->SetTile(Vec2u(i, j), grassTile); 
		}
	}
	// going to make a hint class that inherits from text so this can update
	level->AddText(Vec2f(640, 360) / 2.0f + Vec2f(0.0f, 150.0f), "Hints down here", 12);

	SetScene(level);
}

/*
	Event Function for Loading Credits Scene

	@author(s) Jamuel Bocacao
*/
void BeaverGame::LoadCredits()
{
}

/*
	Event Function for Loading Win Game Scene

	@author(s) Theo Morris
*/
void BeaverGame::LoadWinGame()
{
	auto winGame = make_shared<Scene>(Vec2u(1920, 1080), &m_window, false);
	winGame->AddText(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -300.0f), "You Win", 100);

	auto playAgainEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadLevel);
	winGame->AddButton(Vec2f(1920, 1080) / 2.0f, "Resources/Images/Buttons/PlayAgain.png", "Resources/Audio/Click.wav", playAgainEvent);

	auto returnToMainMenuEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadMenu);
	winGame->AddButton(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -150.0f), "Resources/Images/Buttons/Exit.png", "Resources/Audio/Click.wav", returnToMainMenuEvent);

	SetScene(winGame);
}

/*
	Event Function for Loading Loss Game Scene

	@author(s) Theo Morris
*/
void BeaverGame::LoadGameOver()
{
	auto gameOver = make_shared<Scene>(Vec2u(1920, 1080), &m_window, false);
	gameOver->AddText(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -300.0f), "Game Over", 100);

	auto playAgainEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadLevel);
	gameOver->AddButton(Vec2f(1920, 1080) / 2.0f, "Resources/Images/Buttons/PlayAgain.png", "Resources/Audio/Click.wav", playAgainEvent);

	auto returnToMainMenuEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadMenu);
	gameOver->AddButton(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -150.0f), "Resources/Images/Buttons/Exit.png", "Resources/Audio/Click.wav", returnToMainMenuEvent);

	SetScene(gameOver);
}

void BeaverGame::Quit()
{
	m_window.close();
}
