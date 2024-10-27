#include "Beaver.h"
#include "Level.h"
#include "ParticleSystem.h"

/*
	Creates a Beaver Object

	@author(s) Jamuel Bocacao, Theo Morris and Kaz
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


	// Creates a blood particle system for damaging
	m_bloodParticleSystem = make_shared<ParticleSystem>(30);
	m_bloodParticleSystem->SetPlayTime(0.5f);
	m_bloodParticleSystem->SetTexture(&TextureManager::GetInstance().GetTexture("Resources/Images/Blood.png"));

}

Beaver::~Beaver()
{
	
}

void Beaver::Render(sf::RenderTexture* _sceneBuffer)
{
	if (m_bloodParticleSystem)
	{
		m_bloodParticleSystem->Render(_sceneBuffer);
	}
	Object::Render(_sceneBuffer);
}
/*
	Event Called when another Object comes into contact with a Beaver

	@author(s) Jamuel Bocacao
	@param Object*: Other Object in contact with Beaver
*/
void Beaver::OnBeginContact(Object* _otherObject)
{
	if (_otherObject && _otherObject->IsOfType<Warehouse>())
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
	if (_otherObject && _otherObject->IsOfType<Warehouse>())
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

	@author Jamuel Bocacao and Theo Morris
	@param int: Value of Damage done to Beaver
*/
void Beaver::Damage(int _iDamage)
{
	if (m_bloodParticleSystem)
	{
		m_bloodParticleSystem->Play();
	}

	m_iHealth -= _iDamage;

	if (m_iHealth <= 0)
	{
		if (m_spawnerRef)
		{
			m_spawnerRef->AddBudget(GetCost());
		}
		Destroy();
	}
}
/*
	Handles Updating Beaver

	@author(s) Jamuel Bocacao and Theo Morris
	@param float: Delta Time
*/
void Beaver::Update(float _fDeltaTime)
{
	if (_fDeltaTime == 0) return;
	m_woodClock += _fDeltaTime;

	if (m_animator)
	{
		m_animator->Update(_fDeltaTime);
	}

	if (m_warehouse)
	{
		if (m_woodClock > 1.0f)
		{
			m_woodClock = 0.0f;
			if (m_warehouse)
			{
				m_warehouse->ChangeWoodAmount(-m_iDamage);
				if (m_animator)
				{
					m_animator->ChangeState("Attack");
				}
			}
		}
	}
	else
	{
		auto cellValue = m_currLevel ? m_currLevel->GetFlowFieldValue(m_sprite.getPosition()) : Vec2f(0, 0);
		if (Length(cellValue) > 0)
		{
			m_iVelocity = cellValue;
		}
		AddPosition(m_iVelocity * _fDeltaTime * 64.0f);
		if (m_animator)
		{
			m_animator->ChangeState("Walk");
		}
	}

	if (m_bloodParticleSystem)
	{
		m_bloodParticleSystem->SetEmitterPosition(GetPosition());
		m_bloodParticleSystem->Update(_fDeltaTime);
	}
}