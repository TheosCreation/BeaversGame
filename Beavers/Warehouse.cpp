#include "Warehouse.h"
#include "Player.h"
#include "Level.h"

/*
	Creates a Warehouse Object

	@author(s) Jamuel Bocacao
	@param Vec2f: Position of Warehouse
*/
Warehouse::Warehouse(Vec2f _position) : Object(_position, "Resources/Objects/Warehouse.png", true)
{
	AddBoxCollider(Vec2f(0.0f, 20.0f), Vec2f(128, 24));
	AddBoxCollider(Vec2f(0.0f, 47.0f), Vec2f(128, 30), true);

	m_currLevel->SetFlowFieldGoal(_position - Vec2f(64, 32), _position + Vec2f(96, 64));
}

/*
	Changes the Wood Amount stored in Warehouse

	@author(s) Jamuel Bocacao
	@param int: Number to change amount by 
*/
void Warehouse::ChangeWoodAmount(int _iAmount)
{
	m_iWoodAmount += _iAmount;
}

/*
	Gets the Amount of Wood in Warehouse

	@author(s) Jamuel Bocacao
	@return int: Amount of Wood in Warehouse
*/
int Warehouse::GetWoodAmount()
{
	return m_iWoodAmount;
}

/*
	Begin Contact Event for Warehouse

	@author(s) Jamuel Bocacao
	@param Object*: Other Object overlapping
*/
void Warehouse::OnBeginContact(Object* _other)
{
	// Check to see if overlapping Object is a Player
	Player* player = nullptr;
	if (_other->IsOfType<Player>(&player))
	{
		// Deposit Wood if it is a Player
		ChangeWoodAmount(player->Deposit());
	}
}
