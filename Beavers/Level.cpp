#include "Level.h"

Level::Level(Vec2u _sceneSize, sf::RenderWindow* _window, bool _bUnloadPreviousSceneOnLoad) : Scene(_sceneSize, _window, _bUnloadPreviousSceneOnLoad)
{
	m_world = make_shared<b2World>(b2Vec2_zero);
	m_world->SetContactListener(&m_listener);

	auto player = make_shared<Object>(Vec2f(1920.0f, 1080.0f) / 2.0f, "Resources/Images/Cat.png", m_world, false);
	m_player = player;
	AddGameObject(player);
}

Level::~Level()
{
	m_world.reset();
}

void Level::Update(float _fDeltaTime, sf::RenderWindow* _window)
{
	m_world->Step(_fDeltaTime, 8, 3);

	sf::Vector2f displacement;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		displacement += Vec2f(0.0f, -1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		displacement += Vec2f(-1.0f, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		displacement += Vec2f(0.0f, 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		displacement += Vec2f(1.0f, 0.0f);
	}
	m_player.lock()->ApplyForce(displacement * _fDeltaTime * 300.0f);
}
