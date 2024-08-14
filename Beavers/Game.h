#pragma once
#include "Scene.h"

class Game
{
public:
	Game() = default;

	void Start(string _strWindowTitle);
	void CleanUp();

	void SetScene(shared_ptr<Scene> _scene);
	void LoadPreviousScene();

private:
	void Drag(int _iValue);
	void LoadMenu();
	void LoadGameScene();
	void LoadOptions();

private:
	static inline bool m_bHasStarted = false;
	sf::RenderWindow m_window;

	shared_ptr<Scene> m_currentScene;
	shared_ptr<Scene> m_previousScene;
};
