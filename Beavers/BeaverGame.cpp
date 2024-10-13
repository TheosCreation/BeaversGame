#include "BeaverGame.h"
#include "AudioManager.h"
#include "Level.h"
#include "Warehouse.h"
#include "Player.h"
#include "Tree.h"
#include "Beaver.h"
#include "Text.h"
#include "TileMap.h"
#include "Hint.h"
#include "PerlinNoise.h"
#include <iostream>
#include "BeaverSpawner.h"
/*
	Event Function for Loading Menu Scene

	@author(s) Jamuel Bocacao and Theo Morris
*/
void BeaverGame::LoadMenu()
{
	auto menu = make_shared<Scene>(Vec2u(1920, 1080), &m_window, true);

	//Create the background image
	menu->AddImage(Vec2f(1920, 1080) / 2.0f, "Resources/Images/BeaversInAForest.png", -10);

	//Create the title text
	menu->AddText(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -300.0f), "Beaverpocalypse", 100, sf::Color::Black);
	
	//Create the options button
	auto optionEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadOptions);
	menu->AddButton(Vec2f(1920, 1080) / 2.0f, "Resources/Images/Buttons/Options.png", "Resources/Audio/Click.wav", optionEvent);

	//Create the play button
	auto playEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadLevel);
	menu->AddButton(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -150.0f), "Resources/Images/Buttons/Play.png", "Resources/Audio/Click.wav", playEvent);

	//Create the quit button
	auto quitEvent = make_shared<Event<void, void>>(this, &BeaverGame::Quit);
	menu->AddButton(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, 150.0f), "Resources/Images/Buttons/Quit.png", "Resources/Audio/Click.wav", quitEvent);


	//Starts playing the music for the menus
	AudioManager::GetInstance().PlayMusic("Resources/Music/Menu Music.ogg", sf::seconds(2.05f));

	SetScene(menu);
}

/*
	Event Function for Loading Options Scene

	@author(s) Jamuel Bocacao and Theo Morris
*/
void BeaverGame::LoadOptions()
{
	auto options = make_shared<Scene>(Vec2u(1920, 1080), &m_window, false);

	//Create the background image
	options->AddImage(Vec2f(1920, 1080) / 2.0f, "Resources/Images/BeaversInAForest.png", -10); 

	//Create the title text
	options->AddText(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -300.0f), "Options", 100, sf::Color::Black);

	//Create the sfx volume slider
	auto soundDragEvent = make_shared<Event<void, int>>(&AudioManager::GetInstance(), &AudioManager::SetSoundVolume);
	options->AddText(Vec2f(1920, 1080) / 2.0f + Vec2f(-400.0f, -150.0f), "SFX Volume", 30, sf::Color::Black);
	options->AddSlider(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -150.0f), 50, 100, soundDragEvent);

	//Create the music volume slider
	auto musicDragEvent = make_shared<Event<void, int>>(&AudioManager::GetInstance(), &AudioManager::SetMusicVolume);
	options->AddText(Vec2f(1920, 1080) / 2.0f + Vec2f(-400.0f, 0.0f), "Music Volume", 30, sf::Color::Black);
	options->AddSlider(Vec2f(1920, 1080) / 2.0f, 50, 100, musicDragEvent);

	//Create the back button
	auto backEvent = make_shared<Event<void, void>>((Game*)this, &Game::LoadPreviousScene);
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
	auto level = make_shared<Level>(Vec2u(1920, 1080), &m_window, true);
	SetScene(level);

	// Creates Warehouse
	Warehouse* warehouseRef = level->AddObject<Warehouse>(Vec2f(500, 250)).lock().get();

	// Creates a Player and adds it to the level
	auto player = level->AddObject<Player>(Vec2f(640, 360) / 2.0f);
	// Creates Second Player
	ControlScheme secondPlayerControls;
	secondPlayerControls.Left = sf::Keyboard::Left;
	secondPlayerControls.Up = sf::Keyboard::Up;
	secondPlayerControls.Down = sf::Keyboard::Down;
	secondPlayerControls.Right = sf::Keyboard::Right;
	secondPlayerControls.Interact = sf::Keyboard::RShift;
	auto player2 = level->AddObject<Player>(Vec2f(780, 360) / 2.0f);
	player2.lock()->SetControlScheme(secondPlayerControls);

	// Adds a event to the player
	auto event = make_shared<Event2P<void, shared_ptr<GameObject>, int>>((Scene*)level.get(), &Scene::AddGameObject);
	player.lock()->SetWoodAmountChangeEvent(event);
	player2.lock()->SetWoodAmountChangeEvent(event);

	level->AddObject<Tree>(Vec2f(150, 150));
	
	// Creates Shop(s)
	auto shop1 = make_shared<Shop>(Vec2f(90, 50), 1, "Resources/Images/Objects/AxeShop.png");
	auto shop2 = make_shared<Shop>(Vec2f(38, 50), 1, "Resources/Images/Objects/BootShop.png");
	auto shop3 = make_shared<Shop>(Vec2f(142, 50), 1, "Resources/Images/Objects/BagShop.png");

	level->AddGameObject(shop1);
	level->AddGameObject(shop2);
	level->AddGameObject(shop3);

	level->AddObject<Beaver>(Vec2f(500, 500));
	auto spawner = make_shared<BeaverSpawner>(Vec2f(1000, 1000), level->GetWorld(), "", level.get());
	level->AddGameObject(spawner);

	// Creates TileMap
	// First vector is tilemap size second is tile size
	auto tileMap = make_shared<TileMap>(Vec2u(Vec2f(1920, 1080) / 32.0f) + Vec2u(0, 1), Vec2f(32, 32));
	level->AddGameObject(tileMap);

	// Creates different tile types
	
	PerlinNoise perlin; // Automatic tile gen
	float scale = 0.1f; // Perlin scale

	// Test tiles

	for (int i = 0; i < 1920 / 32; i++)
	{
		for (int j = 0; j < (1080 / 32) + 1; j++)
		{
			float noiseValue = perlin.noise(i * scale, j * scale, 0.0f);
			string texturePath = (noiseValue < 0.0) ? "Resources/Images/Tiles/grass.png" : "Resources/Images/Tiles/dirt.png";
			auto tile = make_shared<Tile>(texturePath);
			tileMap->SetTile(Vec2u(i, j), tile);
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
	auto winGameScene = make_shared<Scene>(Vec2u(1920, 1080), &m_window, false);
	//Create the background image
	winGameScene->AddImage(Vec2f(1920, 1080) / 2.0f, "Resources/Images/BeaversInAForest.png", -10);

	//Create title text
	winGameScene->AddText(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -300.0f), "You Win", 100, sf::Color::Black);

	//Create play again button
	auto playAgainEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadLevel);
	winGameScene->AddButton(Vec2f(1920, 1080) / 2.0f, "Resources/Images/Buttons/PlayAgain.png", "Resources/Audio/Click.wav", playAgainEvent);

	//Create return to main menu button
	auto returnToMainMenuEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadMenu);
	winGameScene->AddButton(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -150.0f), "Resources/Images/Buttons/Exit.png", "Resources/Audio/Click.wav", returnToMainMenuEvent);

	SetScene(winGameScene);
}

/*
	Event Function for Loading Loss Game Scene

	@author(s) Theo Morris
*/
void BeaverGame::LoadGameOver()
{
	auto gameOverScene = make_shared<Scene>(Vec2u(1920, 1080), &m_window, false);
	//Create the background image
	gameOverScene->AddImage(Vec2f(1920, 1080) / 2.0f, "Resources/Images/BeaversInAForest.png", -10);

	//Create title text
	gameOverScene->AddText(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -300.0f), "Game Over", 100, sf::Color::Black);

	//Create play again button
	auto playAgainEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadLevel);
	gameOverScene->AddButton(Vec2f(1920, 1080) / 2.0f, "Resources/Images/Buttons/PlayAgain.png", "Resources/Audio/Click.wav", playAgainEvent);

	//Create return to main menu button
	auto returnToMainMenuEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadMenu);
	gameOverScene->AddButton(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -150.0f), "Resources/Images/Buttons/Exit.png", "Resources/Audio/Click.wav", returnToMainMenuEvent);

	SetScene(gameOverScene);
}

void BeaverGame::Quit()
{
	m_window.close();
}
