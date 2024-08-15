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

	auto player = make_shared<Player>(Vec2f(_sceneSize) / 2.0f, m_world);
	m_player = player;
	AddGameObject(player);

	auto obstacle = make_shared<Object>(Vec2f(500, 250), "Resources/Images/Objects/Obstacle.png", m_world, true);
	obstacle->AddBoxCollider(Vec2f(0.0f, 0.0f), Vec2f(128, 64));
	AddGameObject(obstacle);
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
