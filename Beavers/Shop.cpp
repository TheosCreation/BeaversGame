#include "Shop.h"

/*
	Creates a Shop Object

	@author(s) Jamuel Bocacao
	@param Vec2f: Position of Shop
	@param weak_ptr<b2World>: Scene World
*/
Shop::Shop(Vec2f _position, weak_ptr<b2World> _sceneWorld) : Object(_position, "Resources/Images/Objects/Shop.png", _sceneWorld, true)
{
	m_statUI = make_unique<Image>(_position + Vec2f(0,0), "");
	m_statUI->SetVisibility(false);
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
}

/*
	Overide Render

	@author(s) Jamjam :)
	@param RenderTexture*: Render Texture
*/
void Shop::Render(sf::RenderTexture* _sceneBuffer)
{
	Object::Render(_sceneBuffer);
	m_statUI->Render(_sceneBuffer);
}

