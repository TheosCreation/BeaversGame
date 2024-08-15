#pragma once
#include "Scene.h"
#include "Player.h"
#include "ContactListener.h"

class Level : public Scene
{
public:
	Level(Vec2u _sceneSize, sf::RenderWindow* _window, bool _bUnloadPreviousSceneOnLoad = true);
	~Level();

	void Update(float _fDeltaTime, sf::RenderWindow* _window) override;

private:
	static ContactListener m_listener;

private:
	shared_ptr<b2World> m_world;
	weak_ptr<Player> m_player;
	shared_ptr<Object> obstacle;
};

inline ContactListener Level::m_listener;
