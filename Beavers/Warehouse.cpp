#include "Warehouse.h"
#include "Player.h"
#include "Level.h"

/*
	Creates a Warehouse Object

	@author(s) Jamuel Bocacao
	@param Vec2f: Position of Warehouse
*/

Warehouse::Warehouse(Vec2f _position)
	: Object(_position, "Resources/Objects/Warehouse.png", true),
	m_woodAmountText(std::make_unique<Text>(_position + Vec2f(0, -20), GetWoodAmountString(), "Resources/Fonts/Yogurt Extra.ttf"))
{
	AddBoxCollider(Vec2f(0.0f, 0.0f), Vec2f(128, 128));
	AddBoxCollider(Vec2f(0.0f, 0.0f), Vec2f(128, 128), true);
	m_woodAmountText->SetSize(20);
	m_woodAmountText->SetColour(sf::Color::White);
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
	m_woodAmountText->SetText(GetWoodAmountString());

	if (m_iWoodAmount > 1000000)
	{
		//Win the game
		m_loadWinSceneEvent->execute();
	}
	else if(m_iWoodAmount <= 0)
	{
		//Lose the game
		m_loadLoseSceneEvent->execute();
	}
}
std::string Warehouse::GetWoodAmountString() const {
	return "Wood: " + std::to_string(m_iWoodAmount);
}
/*
	Gets the Amount of Wood in Warehouse

	@author(s) Jamuel Bocacao
	@return int: Amount of Wood in Warehouse
*/
int Warehouse::GetWoodAmount() const
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
void Warehouse::Render(sf::RenderTexture* _sceneBuffer)
{
	Object::Render(_sceneBuffer);
	m_woodAmountText->Render(_sceneBuffer);
}

/*
	Sets the load win scene event member variable

	@author(s) Theo Morris
	@param shared_ptr<Event<void, void>>: Event to the level loading of the win scene
*/
void Warehouse::SetLoadWinSceneEvent(shared_ptr<Event<void, void>> _loadWinSceneEvent)
{
	m_loadWinSceneEvent = _loadWinSceneEvent;
}

/*
	Sets the load lose scene event member variable

	@author(s) Theo Morris
	@param shared_ptr<Event<void, void>>: Event to the level loading of the lose scene
*/
void Warehouse::SetLoadLoseSceneEvent(shared_ptr<Event<void, void>> _loadLoseSceneEvent)
{
	m_loadLoseSceneEvent = _loadLoseSceneEvent;
}
