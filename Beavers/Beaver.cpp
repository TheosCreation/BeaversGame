#include "Beaver.h"
#include "Level.h"

/*
	Creates a Beaver Object

	@author(s) Jamuel Bocacao
	@param Vec2f: Position of Beaver
	@param weak_ptr<b2World>: Scene World
*/
Beaver::Beaver(Vec2f _position) : Object(_position, false)
{
	SetDrawRect(sf::IntRect(0, 0, 907, 505));
	m_animator = make_unique<Animator>(&m_sprite);

	//AddBoxCollider(Vec2f(0, 0), Vec2f(40, 50));
	AddCircleCollider(Vec2f(0, 0), 26.0f, true);

	m_sprite.setScale(0.1f, 0.1f);

	m_animator->AddState("Walk", "Resources/Images/Entities/Beaver/Walk.png", 8, 8);
	m_animator->AddState("HitStanding", "Resources/Images/Entities/Beaver/HitStanding.png", 6, 8);
	m_animator->AddState("DieStanding", "Resources/Images/Entities/Beaver/DieStanding.png", 5, 8);
	m_animator->AddState("Attack", "Resources/Images/Entities/Beaver/Attack.png", 8, 8);
	m_animator->AddState("Stand", "Resources/Images/Entities/Beaver/GroundToStand.png", 5, 8);

	m_woodClock.restart();

}

Beaver::~Beaver()
{
	
}

/*
	Event Called when another Object comes into contact with a Beaver

	@author(s) Jamuel Bocacao
	@param Object*: Other Object in contact with Beaver
*/
void Beaver::OnBeginContact(Object* _otherObject)
{

	if (_otherObject->IsOfType<Warehouse>())
	{
		m_warehouse = dynamic_cast<Warehouse*>(_otherObject);
	}
}

/*
	Event Called when another Object loses contact with a Beaver

	@author(s) Jamuel Bocacao
	@param Object*: Other Object in contact with Beaver
*/
void Beaver::OnEndContact(Object* _otherObject)
{
	if (_otherObject->IsOfType<Warehouse>())
	{
		m_warehouse = nullptr;
	}
}

int Beaver::GetCost() const
{
	return m_iCost;
}

int Beaver::GetRarity() const
{
	return m_iRarity;
}

/*
	Applies Damage to Beaver's Health

	@author Jamuel Bocacao
	@param int: Value of Damage done to Beaver
*/
void Beaver::Damage(int _iDamage)
{
	m_iHealth -= _iDamage;
	if (m_iHealth <= 0)
	{
		m_spawnerRef->AddBudget(GetCost());
		Destroy();
	}
}

/*
	Handles Updating Beaver

	@author(s) Jamuel Bocacao
	@param float: Delta Time
*/
void Beaver::Update(float _fDeltaTime)
{

	m_animator->Update();

	if (m_warehouse)
	{
		// Removes Wood from Warehouse after a certain Period
		if (m_woodClock.getElapsedTime().asSeconds() > 1.0f)
		{
			m_woodClock.restart();
			m_warehouse->ChangeWoodAmount(-1);
			m_animator->ChangeState("Attack");
		}
	}
	else
	{
		auto cellValue = m_currLevel->GetFlowFieldValue(m_sprite.getPosition());
		if (Length(cellValue) > 0)
		{
			m_iVelocity = cellValue;
		}
		AddPosition(m_iVelocity * _fDeltaTime * 64.0f);
		m_animator->ChangeState("Walk");
	}
}
