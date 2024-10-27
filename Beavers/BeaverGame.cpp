#include "BeaverGame.h"
#include "All.h"
#include "Button.h"
#include "Text.h"
#include "PauseManager.h"

/*
	Event Function for Loading Menu Scene

	@author(s) Jamuel Bocacao and Theo Morris
*/
void BeaverGame::LoadMainMenu()
{
	// Creates and sets the scene to the menu scene
	auto menu = make_shared<Scene>(Vec2u(1920, 1080), &m_window, true);
	SetScene(menu);

	//Starts playing the music for the menus
	AudioManager::GetInstance().PlayMusic("Resources/Music/Menu Music.ogg", sf::seconds(2.05f));

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

	//Initialise GamepadMgr/Gamepad(s)
	//GamepadMgr::Instance().Initialize();
}

/*
	Event Function for Loading Options Scene

	@author(s) Jamuel Bocacao and Theo Morris
*/
void BeaverGame::LoadOptions()
{
	// Creates and sets the scene to the options scene
	auto options = make_shared<Scene>(Vec2u(1920, 1080), &m_window, false);
	SetScene(options);

	//Create the background image
	options->AddImage(Vec2f(1920, 1080) / 2.0f, "Resources/Images/BeaversInAForest.png", -10); 

	//Create the title text
	options->AddText(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -300.0f), "Options", 100, sf::Color::Black);

	//Create the sfx volume slider
	auto soundDragEvent = make_shared<Event<void, int>>(&AudioManager::GetInstance(), &AudioManager::SetSoundVolume);
	options->AddText(Vec2f(1920, 1080) / 2.0f + Vec2f(-400.0f, -150.0f), "SFX Volume", 30, sf::Color::Black);
	options->AddSlider(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -150.0f), AudioManager::GetInstance().GetSoundVolume(), 100, soundDragEvent);

	//Create the music volume slider
	auto musicDragEvent = make_shared<Event<void, int>>(&AudioManager::GetInstance(), &AudioManager::SetMusicVolume);
	options->AddText(Vec2f(1920, 1080) / 2.0f + Vec2f(-400.0f, 0.0f), "Music Volume", 30, sf::Color::Black);
	options->AddSlider(Vec2f(1920, 1080) / 2.0f, AudioManager::GetInstance().GetMusicVolume(), 100, musicDragEvent);

	//Create the back button
	auto backEvent = make_shared<Event<void, void>>((Game*)this, &Game::LoadPreviousScene);
	options->AddButton(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, 150.0f), "Resources/Images/Buttons/Back.png", "Resources/Audio/Click.wav", backEvent);

}

/*
	Event Function for Loading Level

	@author(s) Jamuel Bocacao, Theo Morris, Kazuo RDA and George Mitchell
*/
void BeaverGame::LoadLevel()
{
	AudioManager::GetInstance().StopAll();
	PauseManager::GetInstance().SetPaused(false);

	// Creates and sets the scene to the level scene
	auto level = make_shared<Level>(Vec2u(1920, 1080), &m_window, true);
	SetScene(level);

	
	// Creates a background image attached to the pause menu
	shared_ptr<Image> pauseMenuImage = level->AddImage(Vec2f(1920, 1080) / 2.0f, "Resources/Images/BeaversInAForest.png", 10);
	auto openPauseMenuEvent = std::make_shared<Event<void, bool>>(
		static_cast<GameObject*>(pauseMenuImage.get()), &GameObject::SetVisibility); // Creates an event to be able to toggle the pausemenus visibility

	// Create a back to main menu button attached to the pause menu
	auto returnToMainMenuEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadMainMenu);
	shared_ptr<Button> exitToMainMenuButton = level->AddButton(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, 150.0f), "Resources/Images/Buttons/Exit.png", "Resources/Audio/Click.wav", returnToMainMenuEvent, 10);
	pauseMenuImage->AddChild(exitToMainMenuButton);

	// Create a resume button attached to the pause menu
	auto resumeGame = make_shared<Event<void, void>>(&PauseManager::GetInstance(), &PauseManager::TogglePaused);
	shared_ptr<Button> resumeButton = level->AddButton(Vec2f(1920, 1080) / 2.0f - Vec2f(0.0f, 150.0f), "Resources/Images/Buttons/Back.png", "Resources/Audio/Click.wav", resumeGame, 10);
	pauseMenuImage->AddChild(resumeButton);


	// Create the title text attached to the pause menu
	auto pauseMenuTitleText = level->AddText(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -300.0f), "Paused", 100, sf::Color::Black, 10);
	pauseMenuImage->AddChild(pauseMenuTitleText);

	pauseMenuImage->SetVisibility(false); // Set the menu to be not rendered by default
	level->SetOpenPauseMenuEvent(openPauseMenuEvent);


	// Creates Warehouse
	Warehouse* warehouseRef = level->AddObject<Warehouse>(Vec2f(500, 750)).lock().get();

	// Creates and sets the win scene event
	auto loadWinSceneEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadWinGame); 
	warehouseRef->SetLoadWinSceneEvent(loadWinSceneEvent);

	// Creates and sets the lose scene event
	auto loadLoseSceneEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadGameOver);
	warehouseRef->SetLoadLoseSceneEvent(loadLoseSceneEvent);

	// Creates a Player and adds it to the level
	auto player = level->AddObject<Player>(Vec2f(640, 360) / 2.0f);

	// Creates Second Player
	ControlScheme secondPlayerControls;
	secondPlayerControls.Left = sf::Keyboard::Left;
	secondPlayerControls.Up = sf::Keyboard::Up;
	secondPlayerControls.Down = sf::Keyboard::Down;
	secondPlayerControls.Right = sf::Keyboard::Right;
	secondPlayerControls.Interact = sf::Keyboard::RShift;
	secondPlayerControls.Pause = sf::Keyboard::Unknown; // Please review this is to prevent player 2 from receiving input and then unpausing right after pause through player 1
	auto player2 = level->AddObject<Player>(Vec2f(780, 360) / 2.0f);
	player2.lock()->SetControlScheme(secondPlayerControls);	

	// Adds a event to the player
	auto addGameObjectEvent = make_shared<Event2P<void, shared_ptr<GameObject>, int>>((Scene*)level.get(), &Scene::AddGameObject);
	player.lock()->SetWoodAmountChangeEvent(addGameObjectEvent);
	player2.lock()->SetWoodAmountChangeEvent(addGameObjectEvent);

	// Creates the spawner
	auto spawner = make_shared<BeaverSpawner>(Vec2f(1400, 800), level->GetWorld(), "Resources/Images/Objects/Dam.png", warehouseRef);
	level->AddGameObject(spawner);
	spawner->SetAddGameObjectEvent(addGameObjectEvent);

	// Creates the Tree
	auto tree = level->AddObject<Tree>(Vec2f(150, 150));

	// Creates a particle system for tree
	auto woodParticleSystem = make_shared<ParticleSystem>(30);
	woodParticleSystem->SetPlayTime(0.5f);
	woodParticleSystem->SetEmitterPosition(Vec2f(150, 150));
	woodParticleSystem->SetTexture(&TextureManager::GetInstance().GetTexture("Resources/Images/Splinter.png"));
	level->AddGameObject(woodParticleSystem, 10);
	tree.lock()->SetParticleSystemRef(woodParticleSystem);

	// Creates Shop(s)
	auto shop1 = make_shared<Shop>(Vec2f(1350, 150), 30, "Resources/Images/Objects/AxeShop.png", ShopType::Type_Weapon);
	auto shop2 = make_shared<Shop>(Vec2f(1150, 150), 30, "Resources/Images/Objects/BootShop.png", ShopType::Type_Speed);
	auto shop3 = make_shared<Shop>(Vec2f(1550, 150), 30, "Resources/Images/Objects/BagShop.png", ShopType::Type_Bag);
	level->AddGameObject(shop1);
	level->AddGameObject(shop2);
	level->AddGameObject(shop3);


	// Creates TileMap
	auto tileMap = make_shared<TileMap>(Vec2u(Vec2f(1920, 1080) / 32.0f) + Vec2u(0, 1), Vec2f(32, 32));
	level->AddGameObject(tileMap);

	// Creates different tile types
	PerlinNoise perlin; // Automatic tile gen
	float scale = 0.1f; // Perlin scale

	for (int i = 0; i < 1920 / 32; i++)
	{
		for (int j = 0; j < (1080 / 32) + 1; j++)
		{
			float noiseValue = float(perlin.noise(i * scale, j * scale, 0.0f));
			string texturePath = (noiseValue < 0.0) ? "Resources/Images/Tiles/grass.png" : "Resources/Images/Tiles/dirt.png";
			auto tile = make_shared<Tile>(texturePath);
			tileMap->SetTile(Vec2u(i, j), tile);
		}
	}

	// Creates and assigns the player1 a hint text
	Hint* player1Hint = level->AddObject<Hint>(Vec2f(0, 0)).lock().get();
	player.lock()->SetHintRef(player1Hint);

	// Creates and assigns the player2 a hint text
	Hint* player2Hint = level->AddObject<Hint>(Vec2f(0,0)).lock().get();
	player2.lock()->SetHintRef(player2Hint);
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
	// Creates and sets the scene to the win game scene
	auto winGameScene = make_shared<Scene>(Vec2u(1920, 1080), &m_window, false);
	SetScene(winGameScene);

	//Create the background image
	winGameScene->AddImage(Vec2f(1920, 1080) / 2.0f, "Resources/Images/BeaversInAForest.png", -10);

	//Create title text
	winGameScene->AddText(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -300.0f), "You Win", 100, sf::Color::Black);

	//Create play again button
	auto playAgainEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadLevel);
	winGameScene->AddButton(Vec2f(1920, 1080) / 2.0f, "Resources/Images/Buttons/PlayAgain.png", "Resources/Audio/Click.wav", playAgainEvent);

	//Create return to main menu button
	auto returnToMainMenuEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadMainMenu);
	winGameScene->AddButton(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -150.0f), "Resources/Images/Buttons/Exit.png", "Resources/Audio/Click.wav", returnToMainMenuEvent);
}

/*
	Event Function for Loading Loss Game Scene

	@author(s) Theo Morris
*/
void BeaverGame::LoadGameOver()
{
	// Creates and sets the scene to the game over scene
	auto gameOverScene = make_shared<Scene>(Vec2u(1920, 1080), &m_window, false);	
	SetScene(gameOverScene);

	// Create the background image
	gameOverScene->AddImage(Vec2f(1920, 1080) / 2.0f, "Resources/Images/BeaversInAForest.png", -10);

	// Create title text
	gameOverScene->AddText(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -300.0f), "Game Over", 100, sf::Color::Black);

	// Create play again button
	auto playAgainEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadLevel);
	gameOverScene->AddButton(Vec2f(1920, 1080) / 2.0f, "Resources/Images/Buttons/PlayAgain.png", "Resources/Audio/Click.wav", playAgainEvent);

	// Create return to main menu button
	auto returnToMainMenuEvent = make_shared<Event<void, void>>(this, &BeaverGame::LoadMainMenu);
	gameOverScene->AddButton(Vec2f(1920, 1080) / 2.0f + Vec2f(0.0f, -150.0f), "Resources/Images/Buttons/Exit.png", "Resources/Audio/Click.wav", returnToMainMenuEvent);
}

void BeaverGame::Quit()
{
	m_window.close();
}
