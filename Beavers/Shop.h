#pragma once
#include "Object.h"
#include "PlayerStats.h"
#include "Image.h"
class Shop : public Object
{
public:
	Shop(Vec2f _position, weak_ptr<b2World> _sceneWorld);

	void SetItem(PlayerStats _playerStats);
	void SetCost(int _iCost);

	virtual void Render(sf::RenderTexture* _sceneBuffer) override;

private:
	PlayerStats m_statUpgrade;
	int m_iCost = 0;
	unique_ptr<Image> m_statUI;
};

