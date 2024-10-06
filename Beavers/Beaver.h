#pragma once
#include "Warehouse.h"

class Beaver : public Object
{
public:
	Beaver(Vec2f _position);

	void OnBeginContact(Object* _otherObject) override;
	void OnEndContact(Object* _otherObject) override;

	void Update(float _fDeltaTime) override;

private:
	Warehouse* m_warehouse = nullptr;
	sf::Clock m_woodClock;
};

