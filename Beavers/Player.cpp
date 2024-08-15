#include "Player.h"

/*
	Creates a Player's

	@author Jamuel Bocacao
	@param Vec2f: Start Position
	@param shared_ptr<b2World>: Scene World
*/
Player::Player(Vec2f _position, shared_ptr<b2World> _world) : Object(_position, "Resources/Images/Entities/Player.png", _world, false)
{
	SetDrawRect(sf::IntRect(0, 0, 16, 16));
	AddBoxCollider(Vec2f(0, 6), Vec2f(16, 2), false);
}

/*
	Player's Update Procedure

	@author Jamuel Bocacao
	@param float: Delta Time
*/
void Player::Update(float _fDeltaTime)
{
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

	ApplyForce(displacement * _fDeltaTime * 1000.0f * m_fSpeed);
}
