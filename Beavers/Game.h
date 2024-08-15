#pragma once
#include "Scene.h"

class Game
{
public:
	Game() = default;

	virtual void Start(string _strWindowTitle) final;
	virtual void CleanUp() final;

	virtual void SetScene(shared_ptr<Scene> _scene) final;
	virtual void LoadPreviousScene() final;

private:
	virtual void LoadMenu() abstract;
	virtual void LoadOptions() abstract;
	virtual void LoadLevel() abstract;

protected:
	sf::RenderWindow m_window;

private:
	static inline bool m_bHasStarted = false;

	shared_ptr<Scene> m_currentScene;
	shared_ptr<Scene> m_previousScene;
};
