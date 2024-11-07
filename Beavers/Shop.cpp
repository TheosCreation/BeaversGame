#include "Shop.h"
#include "Player.h"
#include "Level.h"
#include <iostream>

/*
	Creates a Shop Object

	@author(s) Jamuel Bocacao and George Mitchell
	@param Vec2f: Position of Shop
*/

Shop::Shop(Vec2f _position, int _baseCost, std::string _spriteImage, ShopType _shopType) : Object(_position, _spriteImage, true)
{
	m_WarehouseRef = m_currLevel->GetObjectOfType<Warehouse>().lock().get();
	//m_statUI = make_unique<Image>(_position + Vec2f(0,0), "");
	//m_statUI->SetVisibility(false);

	m_iCost = _baseCost;

	m_costText = make_unique<Text>(Vec2f(_position.x - 20, _position.y - 15) + Vec2f(20.0f, -60.0f), std::to_string(m_iCost), "Resources/Fonts/AlteHaasGroteskBold.ttf");

	AddBoxCollider(Vec2f(0, 0), Vec2f((float)m_sprite.getTexture()->getSize().x, (float)m_sprite.getTexture()->getSize().y));
	AddBoxCollider(Vec2f(0, (float)m_sprite.getTexture()->getSize().y), Vec2f((float)m_sprite.getTexture()->getSize().x, (float)m_sprite.getTexture()->getSize().y), true);

	m_shopType = _shopType;
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


/*
	Increase players stats

	@author(s) George Mitchell
	@param Playerstats ref: Reference to the players stats
*/
void Shop::ApplyItem(PlayerStats& _playerStats)
{
	if (m_WarehouseRef->GetWoodAmount() >= GetCost())
	{
		switch (m_shopType)
		{
		case Type_Weapon:
			_playerStats.m_fDamage *= 1.2f;
			break;
		case Type_Speed:
			_playerStats.m_iSpeed += 12;
			break;
		case Type_Bag:
			_playerStats.m_fCapacity *= 1.2f;
			break;
		default:
			break;
		}
		m_WarehouseRef->ChangeWoodAmount(-m_iCost);
		std::cout << m_WarehouseRef->GetWoodAmount() << std::endl;
		int newCost = static_cast<int>(m_iCost * 1.15);
		SetCost(newCost);
	}
}

/*
	Returns shops cost

	@author(s) George Mitchell
*/
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
	//m_statUI->Render(_sceneBuffer);

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