#pragma once
#include "Scene.h"
#include "Player.h"
#include "ContactListener.h"

class Level : public Scene
{
public:
	Level(Vector2u _sceneSize, sf::RenderWindow* _window, bool _bUnloadPreviousSceneOnLoad = true);
	~Level();

	void Update(float _fDeltaTime, sf::RenderWindow* _window) override;

<<<<<<< HEAD
	void AddObject(Vec2f _position, string _strTexturePath, bool _bIsStatic);
	void AddPlayer(Vec2f _position);
=======
	weak_ptr<Object> AddObject(Vector2f _position, string _strTexturePath, bool _bIsStatic);
	void AddPlayer(Vector2f _position);
>>>>>>> 7205161f70f02e837f174a86765637b9b1d476fe

private:
	static ContactListener m_listener;

private:
	shared_ptr<b2World> m_world;
};

inline ContactListener Level::m_listener;
