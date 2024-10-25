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

	m_costText = make_unique<Text>(Vec2f(_position.x - 25, _position.y - 40) + Vec2f(20.0f, -60.0f), std::to_string(m_iCost), "Resources/Fonts/AlteHaasGroteskBold.ttf");

	AddBoxCollider(Vec2f(0, 0), Vec2f((float)m_sprite.getTexture()->getSize().x, (float)m_sprite.getTexture()->getSize().y));
	AddBoxCollider(Vec2f(0, (float)m_sprite.getTexture()->getSize().y), Vec2f((float)m_sprite.getTexture()->getSize().x, (float)m_sprite.getTexture()->getSize().y), true);

	switch (_shopType)
	{
	case Type_Weapon:
		m_statUpgrade.m_iDamage = 10;
		m_statUpgrade.m_iCapacity = 0;
		m_statUpgrade.m_iSpeed = 0;
		break;
	case Type_Speed:
		m_statUpgrade.m_iDamage = 0;
		m_statUpgrade.m_iCapacity = 0;
		m_statUpgrade.m_iSpeed = 12;
		break;
	case Type_Bag:
		m_statUpgrade.m_iDamage = 0;
		m_statUpgrade.m_iCapacity = 100;
		m_statUpgrade.m_iSpeed = 0;
		break;
	default:
		break;
	}
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
	if (m_WarehouseRef->GetWoodAmount() >= GetCost())
	{
		_playerStats += m_statUpgrade;
		m_WarehouseRef->ChangeWoodAmount(-m_iCost);
		std::cout << m_WarehouseRef->GetWoodAmount() << std::endl;
		int newCost = static_cast<int>(m_iCost * 1.15);
		SetCost(newCost);
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