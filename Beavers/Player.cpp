#include "Player.h"
#include "Warehouse.h"

/*
	Creates a Player's

	@author Jamuel Bocacao
	@param Vec2f: Start Position
	@param weak_ptr<b2World>: Scene World
*/
Player::Player(Vec2f _position, weak_ptr<b2World> _world) : Object(_position, "Resources/Images/Entities/Player.png", _world, false)
{
	SetDrawRect(sf::IntRect(0, 16, 16, 16));
	AddBoxCollider(Vec2f(0, 6), Vec2f(12, 4), false);	// Collider
	AddCircleCollider(Vec2f(0, 6), 12, true);			// Interaction Range Sensor
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
	if (sf::Keyboard::isKeyPressed(m_controlScheme.Up))
	{
		displacement += Vec2f(0.0f, -1.0f);
	}
	if (sf::Keyboard::isKeyPressed(m_controlScheme.Left))
	{
		displacement += Vec2f(-1.0f, 0.0f);
		m_sprite.setScale(-1, 1);
	}
	if (sf::Keyboard::isKeyPressed(m_controlScheme.Down))
	{
		displacement += Vec2f(0.0f, 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(m_controlScheme.Right))
	{
		displacement += Vec2f(1.0f, 0.0f);
		m_sprite.setScale(1, 1);
	}

	ApplyForce(displacement * _fDeltaTime * 1000.0f * m_fSpeed);
}

/*
	Sets the Player's Controls

	@author Jamuel Bocacao
	@param ControlScheme: Struct containing Keybinds
*/
void Player::SetControlScheme(ControlScheme _scheme)
{
	m_controlScheme = _scheme;
}

/*
	Warehouse Deposit Function

	@author Jamuel Bocacao
	@return int: Wood Amount to deposit into Warehouse
*/
int Player::Deposit()
{
	int iDepositAmount = m_iWoodAmount;
	m_iWoodAmount = 0;
	return iDepositAmount;
}
