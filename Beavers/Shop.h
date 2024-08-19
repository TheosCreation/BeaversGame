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
	int GetCost();

	virtual void Render(sf::RenderTexture* _sceneBuffer) override;
	virtual void OnBeginContact(Object* _otherObject) override;
	virtual void OnEndContact(Object* _otherObject) override;

private:
	PlayerStats m_statUpgrade;
	int m_iCost = 0;
	unique_ptr<Image> m_statUI;
};

