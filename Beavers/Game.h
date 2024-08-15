#pragma once
#include "Scene.h"

class Game
{
public:
	Game() = default;
	~Game() = default;

	virtual void Start(string _strWindowTitle) final;
	virtual void CleanUp() final;

	virtual void SetScene(shared_ptr<Scene> _scene) final;
	virtual void LoadPreviousScene() final;

private:
	Game(const Game& _copy) = delete;
	Game& operator= (const Game& _copy) = delete;

private:
	virtual void LoadMenu() abstract;

protected:
	sf::RenderWindow m_window;

private:
	static inline bool m_bHasStarted = false;

	shared_ptr<Scene> m_currentScene;
	shared_ptr<Scene> m_previousScene;
};
