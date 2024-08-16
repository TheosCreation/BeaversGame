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

	weak_ptr<Object> AddObject(Vec2f _position, string _strTexturePath, bool _bIsStatic);
	void AddPlayer(Vec2f _position);
	void AddWarehouse(Vec2f _position);

private:
	static ContactListener m_listener;

private:
	shared_ptr<b2World> m_world;
};

inline ContactListener Level::m_listener;
