#pragma once
#include "Scene.h"
#include "Player.h"
#include "ContactListener.h"
#include "FlowField.h"

class Level : public Scene
{
public:
	Level(Vec2u _sceneSize, sf::RenderWindow* _window, bool _bUnloadPreviousSceneOnLoad = true);
	~Level();

	void Update(float _fDeltaTime, sf::RenderWindow* _window) override;

	// Add Object Methods
	weak_ptr<Object> AddObject(Vec2f _position, string _strTexturePath, bool _bIsStatic);
	template <std::derived_from<Object> T>
	weak_ptr<T> AddObject(Vec2f _position);

	// Find Object Methods
	template <std::derived_from<GameObject> T>
	weak_ptr<T> GetObjectOfType();
	template <std::derived_from<GameObject> T>
	vector<weak_ptr<T>> GetObjectsOfType();

	shared_ptr<b2World> GetWorld();

private:
	static ContactListener m_listener;

private:
	shared_ptr<b2World> m_world;
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

/*
	Gets First Object of Type T

	@author Jamuel Bocacao
	@param <T>: GameObject Subclass to search for
	@return weak_ptr<T>: Reference to found Object
*/
template<std::derived_from<GameObject> T>
inline weak_ptr<T> Level::GetObjectOfType()
{
	// Iterate through Scene Objects
	for (auto layer : m_objects)
	{
		for (auto object : layer.second)
		{
			// Check if Object is of specified Class Type
			if (object->IsOfType<T>())
			{
				return std::dynamic_pointer_cast<T>(object);
			}
		}
	}
	return weak_ptr<T>();
}
