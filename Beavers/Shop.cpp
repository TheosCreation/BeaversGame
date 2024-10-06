#include "Shop.h"
#include "Player.h"
#include <iostream>

/*
	Creates a Shop Object

	@author(s) Jamuel Bocacao and George Mitchell
	@param Vec2f: Position of Shop
*/
Shop::Shop(Vec2f _position, weak_ptr<b2World> _sceneWorld, Warehouse* _warehouseRef, int _baseCost, std::string _spriteImage) : Object(_position, _spriteImage, _sceneWorld, true)
{
	m_WarehouseRef = _warehouseRef;
	m_statUI = make_unique<Image>(_position + Vec2f(0,0), "");
	m_statUI->SetVisibility(false);

	m_iCost = _baseCost;

	m_costText = make_unique<Text>(Vec2f(_position.x - 25, _position.y - 40) + Vec2f(20.0f, -2.0f), std::to_string(m_iCost), "Resources/Fonts/Yogurt Extra.ttf");

	AddBoxCollider(Vec2f(0, 0), Vec2f(m_sprite.getTexture()->getSize().x, m_sprite.getTexture()->getSize().y));
	AddBoxCollider(Vec2f(0, m_sprite.getTexture()->getSize().y), Vec2f(m_sprite.getTexture()->getSize().x, m_sprite.getTexture()->getSize().y), true);
}

/*
	Sets player stats struct in shop

	@author(s) George Mitchell
	@param PlayerStats: PlayerStats struct for upgrading
*/
void Shop::SetItem(PlayerStats _playerStats)
{
	m_statUpgrade = _playerStats;
}

/*
	Set shop upgrade cost

	@author(s) George Mitchell
	@param int: New cost to set to
*/
void Shop::SetCost(int _iCost)
{
	m_iCost = _iCost;
	m_costText->SetText(std::to_string(m_iCost));
	//m_costText = make_unique<Text>(Vec2f(m_costText->GetPosition().x, m_costText->GetPosition().y) + Vec2f(20.0f, -2.0f), std::to_string(m_iCost), "Resources/Fonts/Yogurt Extra.ttf");
}

void Shop::ApplyItem(PlayerStats& _playerStats)
{
	if(m_WarehouseRef->GetWoodAmount() >= GetCost())
	{
		std::cout << "We buyin" << std::endl;

		_playerStats += m_statUpgrade;
		m_WarehouseRef->ChangeWoodAmount(-m_iCost);
		std::cout << m_WarehouseRef->GetWoodAmount() << std::endl;
		SetCost(m_iCost * 2);
	}
}

int Shop::GetCost()
{
	return m_iCost;
}

/*
	Overide Render

	@author(s) Jamuel Bocacao and George Mitchell
	@param RenderTexture*: Render Texture
*/
void Shop::Render(sf::RenderTexture* _sceneBuffer)
{
	Object::Render(_sceneBuffer);
	m_statUI->Render(_sceneBuffer);

	m_costText->Render(_sceneBuffer);
}

void Shop::OnBeginContact(Object* _otherObject)
{
	// Check to see if overlapping Object is a Player
	Player* player = nullptr;
	if (_otherObject->IsOfType<Player>(&player))
	{
		player->SetShopRef(this);
	}
}

void Shop::OnEndContact(Object* _otherObject)
{
	// Check to see if overlapping Object is a Player
	Player* player = nullptr;
	if (_otherObject->IsOfType<Player>(&player))
	{
		player->SetShopRef(nullptr);
	}
}