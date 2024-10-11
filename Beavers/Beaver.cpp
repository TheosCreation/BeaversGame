#include "Beaver.h"
#include "Level.h"

/*
	Creates a Beaver Object

	@author(s) Jamuel Bocacao
	@param Vec2f: Position of Beaver
	@param weak_ptr<b2World>: Scene World
*/
Beaver::Beaver(Vec2f _position) : Object(_position, "Resources/Objects/Beaver.png", false)
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

/*
	Handles Updating Beaver

	@author(s) Jamuel Bocacao
	@param float: Delta Time
*/
void Beaver::Update(float _fDeltaTime)
{
	if (m_warehouse)
	{
		// Removes Wood from Warehouse after a certain Period
		if (m_woodClock.getElapsedTime().asSeconds() > 5.0f)
		{
			m_woodClock.restart();
			m_warehouse->ChangeWoodAmount(-1);
		}
	}
	else
	{
		m_currLevel->GetFlowFieldValue(m_sprite.getPosition());
	}
}
