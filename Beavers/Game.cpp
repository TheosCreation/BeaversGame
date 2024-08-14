#include "Game.h"
#include "AudioManager.h"

/*
	Begins the Game Loop

	@author Jamuel Bocacao
	@param string: Title of Window	
*/
void Game::Start(string _strWindowTitle)
{
	// Prevent Game from starting
	if (m_bHasStarted) return;
	m_window.create(sf::VideoMode(1280, 720), _strWindowTitle);
	m_bHasStarted = true;

	LoadMenu();

	// Begin Loop
	while (m_window.isOpen())
	{
		// Read Events
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					m_window.close();
					break;
				}
				default:
				{
					m_currentScene->ProcessEvents(event, &m_window);
					break;
				}
			}
		}

		// Display Scene Objects
		m_window.clear();
		m_currentScene->Render(&m_window);
		m_window.display();
	}

	m_bHasStarted = false;
	
	CleanUp();
}

/*
	Handles cleaning up application after close window event is called

	@author Jamuel Bocacao
*/
void Game::CleanUp()
{
	TextureManager::GetInstance().UnloadAllTextures();
}

/*
	Handles switching between Scenes

	@author Jamuel Bocacao
	@param shared_ptr<Scene>: Scene to be loaded in
*/
void Game::SetScene(shared_ptr<Scene> _scene)
{
	// Delete previous Scene if not returning to previous Scene
	if (m_previousScene.get() && _scene != m_previousScene)
	{
		m_previousScene.reset();
	}

	// Check if Scene can be returned from
	if (m_currentScene && !_scene->GetUnloadPreviousScene())
	{
		// Store Current Scene as Previous Scene
		m_previousScene = m_currentScene;
		m_currentScene = _scene;
	}
	else
	{
		// Unload Current Scene then store next Scene
		m_currentScene = _scene;
	}
}

/*
	Loads Previous Scene

	@author Jamuel Bocacao
*/
void Game::LoadPreviousScene()
{
	// Check if there is a previous Scene loaded
	if (!m_previousScene.get()) return;
	SetScene(m_previousScene);
}

void Game::Drag(int _iValue)
{
	printf("%i\n", _iValue);
}

void Game::LoadMenu()
{
	auto menu = make_shared<Scene>(Vec2u(1920, 1080), &m_window, true);
	auto event = make_shared<Event<void, void>>(this, &Game::LoadOptions);
	menu->AddImage(Vec2f(1920, 1080) / 2.0f, "Resources/Images/download.jpeg");
	menu->AddButton(Vec2f(1920, 1080) / 2.0f, "Resources/Images/Buttons/Options.png", "Resources/Audio/Click.wav", event);
	
	AudioManager::GetInstance().PlayMusic("Resources/Music/Menu Music.ogg", sf::seconds(2.05f));
	
	SetScene(menu);
}

void Game::LoadOptions()
{
	auto options = make_shared<Scene>(Vec2u(1920, 1080), &m_window, false);
	auto event = make_shared<Event<void, void>>(this, &Game::LoadPreviousScene);
	options->AddButton(Vec2f(1920, 1080) / 2.0f, "Resources/Images/Buttons/Back.png", "Resources/Audio/Click.wav", event);
	SetScene(options);
}
