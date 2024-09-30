#include "Player.h"
#include "Warehouse.h"
#include "WoodChange.h"
#include "Tree.h"
#include <iostream>

/*
	Creates a Player's

	@author Jamuel Bocacao
	@param Vec2f: Start Position
	@param weak_ptr<b2World>: Scene World
*/
Player::Player(Vec2f _position, weak_ptr<b2World> _world) : Object(_position, _world, false)
{
	SetDrawRect(sf::IntRect(0, 16, 16, 16));
	AddBoxCollider(Vec2f(0, 6), Vec2f(12, 4), false);	// Collider
	AddCircleCollider(Vec2f(0, 6), 12, true);			// Interaction Range Sensor

	m_animator = make_unique<Animator>(&m_sprite);
	m_animator->AddState("Running", "Resources/Images/Entities/Run.png", 4, 8);
	m_animator->AddState("Idle", "Resources/Images/Entities/Idle.png", 4, 8);
	m_animator->AddState("Attack", "Resources/Images/Entities/Attack.png", 5, 8, "Idle");
}

/*
	Player's Update Procedure

	@author Jamuel Bocacao
	@param float: Delta Time
*/
void Player::Update(float _fDeltaTime)
{
	// Updates Current Animation Frame
	m_animator->Update();

	// Handles Player Movement
	sf::Vector2f displacement;
	if (!m_bInteracting)
	{
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

		float length = sqrt(powf(displacement.x, 2.0f) + powf(displacement.y, 2.0f));
		if (length > 0)
		{
			m_animator->ChangeState("Running");

			displacement /= length;
			AddPosition(displacement * _fDeltaTime * m_fSpeed);
			//ApplyForce(displacement * _fDeltaTime * 1000.0f * m_fSpeed);

			// Clamp Speed
			b2Vec2 velocity = m_body->GetLinearVelocity();
			float velSpeed = velocity.Normalize();
			if (velSpeed > 2.0f)
			{
				m_body->SetLinearVelocity(2.0f * velocity);
			}
		}
		else
		{
			m_animator->ChangeState("Idle");
		}
	}
	else
	{
		if (m_interactClock.getElapsedTime().asSeconds() > 4.0f/8.0f)
		{
			if (m_bNearTree)
			{
				ExecuteWoodAmountChangeEvent(10);
				m_iWoodAmount += 10;
			}
			else if (m_shopRef)
			{
				m_shopRef->ApplyItem(m_playerStats);
			}
			m_bInteracting = false;
		}
	}
	
	if (sf::Keyboard::isKeyPressed(m_controlScheme.Interact))
	{
		if (!m_bInteracting)
		{
			if (m_bNearTree)
			{
				m_animator->ChangeState("Attack");
				m_interactClock.restart();
				m_bInteracting = true;
			}
			else if (m_shopRef)
			{
				m_interactClock.restart();
				m_bInteracting = true;
			}
		}
	}
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
	Sets the Event that spawns a UI indicator when wood amount has changed

	@author Jamuel Bocacao
	@param shared_ptr<Event2P<void, shared_ptr<GameObject>, int>>: Level's AddGameObject() function
*/
void Player::SetWoodAmountChangeEvent(shared_ptr<Event2P<void, shared_ptr<GameObject>, int>> _woodAmountChangeEvent)
{
	m_woodAmountChangeEvent = _woodAmountChangeEvent;
}

/*
	Executes an Event when the amount of Wood a Player if holding changes

	@author Jamuel Bocacao
	@param int: Change in Wood amount
*/
void Player::ExecuteWoodAmountChangeEvent(int _iAmount)
{
	auto woodChange = make_shared<WoodChange>(GetPosition() + Vec2f(15.0f, -15.0f), _iAmount);
	m_woodAmountChangeEvent->execute(woodChange, 100);
}

void Player::OnBeginContact(Object* _other)
{
	if (_other->IsOfType<Tree>())
	{
		m_bNearTree = true;
	}
}

void Player::OnEndContact(Object* _other)
{
	if (_other->IsOfType<Tree>())
	{
		m_bNearTree = false;
	}
}

/*
	Set shop reference Function

	@author George Mitchell
	@param Shop*: Shop reference to store
*/
void Player::SetShopRef(Shop* _shop)
{
	m_shopRef = _shop;
}

/*
	Warehouse Deposit Function

	@author Jamuel Bocacao
	@return int: Wood Amount to deposit into Warehouse
*/
int Player::Deposit()
{
	// Spawns a Minus Item Element
	if (m_iWoodAmount != 0)
	{
		ExecuteWoodAmountChangeEvent(-m_iWoodAmount);
	}

	int iDepositAmount = m_iWoodAmount;
	m_iWoodAmount = 0;
	return iDepositAmount;
}
