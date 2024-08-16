#pragma once
#include "Object.h"
class Warehouse : public Object
{
public:
	Warehouse(Vec2f _position, weak_ptr<b2World> _sceneWorld);

	void ChangeWoodAmount(int _iAmount);
	int GetWoodAmount();

	void OnBeginContact(Object* _other) override;

private:
	int m_iWoodAmount = 0;
};

