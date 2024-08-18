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

	PlayerStats GetItem();

	virtual void Render(sf::RenderTexture* _sceneBuffer) override;
	virtual void OnBeginContact(Object* _otherObject);
	virtual void OnEndContact(Object* _otherObject);

private:
	PlayerStats m_statUpgrade;
	int m_iCost = 0;
	unique_ptr<Image> m_statUI;
};

