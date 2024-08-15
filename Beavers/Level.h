#pragma once
#include "Scene.h"
#include "Object.h"
#include "ContactListener.h"

class Level : public Scene
{
public:
	Level(Vector2u _sceneSize, sf::RenderWindow* _window, bool _bUnloadPreviousSceneOnLoad = true);
	~Level();

	void Update(float _fDeltaTime, sf::RenderWindow* _window) override;

private:
	static ContactListener m_listener;

private:
	shared_ptr<b2World> m_world;
	weak_ptr<Object> m_player;
};

inline ContactListener Level::m_listener;
