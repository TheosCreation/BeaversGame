#include "Level.h"

/*
	Creates a Level

	@author Jamuel Bocacao
	@param Vec2u: Size of Scene in Pixels
	@param sf::RenderWindow*: Window Handle
	@param bool: Whether previous Scene should be unloaded when this Scene is loaded
*/
Level::Level(Vec2u _sceneSize, sf::RenderWindow* _window, bool _bUnloadPreviousSceneOnLoad) : Scene(_sceneSize, _window, _bUnloadPreviousSceneOnLoad)
{
	m_world = make_shared<b2World>(b2Vec2_zero);
	m_world->SetContactListener(&m_listener);
}

/*
	Handles unloading Scene
*/
Level::~Level()
{
	m_world.reset();
}

/*
	Handles updating objects 

	@author Jamuel Bocacao
	@param float: Delta Time
	@param sf::RenderWindow*: Window Handle
*/
void Level::Update(float _fDeltaTime, sf::RenderWindow* _window)
{
	// Updates Scene Objects first
	Scene::Update(_fDeltaTime, _window);

	m_world->Step(_fDeltaTime, 8, 3);
}

/*
	Adds an Object to Scene

	@author Jamuel Bocacao
	@param Vec2f: Position of Object
	@param string: Texture File Path
	@param bool: Object can move
*/
void Level::AddObject(Vec2f _position, string _strTexturePath, bool _bIsStatic)
{
	auto object = make_shared<Object>(_position, _strTexturePath, m_world, true);
	AddGameObject(object);
}

/*
	Adds a Player to Level at a certain Position (Currently Adds 1 do not use twice)

	@author Jamuel Bocacao
	@param Vec2f: Start Position
*/
void Level::AddPlayer(Vec2f _position)
{
	AddGameObject(make_shared<Player>(_position, m_world));
}
