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
	template <std::derived_from<Object> T>
	weak_ptr<T> AddObject(Vec2f _position);

	static shared_ptr<b2World> GetWorld();

private:
	static ContactListener m_listener;

private:
	static inline shared_ptr<b2World> m_world;
};

inline ContactListener Level::m_listener;

/*
	Adds an Object to Scene

	@author Jamuel Bocacao
	@param <T>: Object Subclass to be instantiated
	@param Vec2f: Position of Object
	@return weak_ptr<T>: Reference to Object
*/
template <std::derived_from<Object> T>
inline weak_ptr<T> Level::AddObject(Vec2f _position)
{
	auto object = make_shared<T>(_position);
	AddGameObject(object);
	return object;
}
