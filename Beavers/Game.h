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
	shared_ptr<Scene> GetCurrentScene();
	virtual void LoadPreviousScene() final;

	void SetTimeScale(float _newTimeScale);

private:
	Game(const Game& _copy) = delete;
	Game& operator= (const Game& _copy) = delete;

private:
	virtual void LoadMainMenu() abstract;

protected:
	sf::RenderWindow m_window;

private:
	static inline bool m_bHasStarted = false;
	float m_fTimeScale = 1.0f; // Time scale used to speed up or slow/stop the games updates

	shared_ptr<Scene> m_currentScene;
	shared_ptr<Scene> m_previousScene;
};
