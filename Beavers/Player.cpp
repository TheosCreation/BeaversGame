#include "Player.h"

/*
	Creates a Player's

	@author Jamuel Bocacao
	@param Vec2f: Start Position
	@param shared_ptr<b2World>: Scene World
*/
Player::Player(Vec2f _position, shared_ptr<b2World> _world) : Object(_position, "Resources/Images/Entities/Player.png", _world, false)
{
	SetDrawRect(sf::IntRect(0, 16, 16, 16));
	AddBoxCollider(Vec2f(0, 6), Vec2f(16, 4), false);
}

/*
	Player's Update Procedure

	@author Jamuel Bocacao
	@param float: Delta Time
*/
void Player::Update(float _fDeltaTime)
{
	// Updates Current Animation Frame
	if (m_animationClock.getElapsedTime().asSeconds() > 3.0f / 24.0f)
	{
		m_animationClock.restart();
		m_iAnimationFrame++;

		if (m_iAnimationFrame > 3)
		{
			m_iAnimationFrame = 0;
		}

		m_sprite.setTextureRect(sf::IntRect(16 * m_iAnimationFrame, 16, 16, 16));
	}

	// Handles Player Movement
	sf::Vector2f displacement;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		displacement += Vec2f(0.0f, -1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		displacement += Vec2f(-1.0f, 0.0f);
		m_sprite.setScale(-1, 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		displacement += Vec2f(0.0f, 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		displacement += Vec2f(1.0f, 0.0f);
		m_sprite.setScale(1, 1);
	}

	ApplyForce(displacement * _fDeltaTime * 1000.0f * m_fSpeed);
}
