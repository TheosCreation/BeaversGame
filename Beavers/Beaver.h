#pragma once
#include "Warehouse.h"
#include "Animator.h"

class Beaver : public Object
{
public:
	Beaver(Vec2f _position);

	void OnBeginContact(Object* _otherObject) override;
	void OnEndContact(Object* _otherObject) override;

	void Damage(int _iDamage);

	void Update(float _fDeltaTime) override;

private:
	Vec2f m_velocity;

	int m_iHealth = 10;

	Warehouse* m_warehouse = nullptr;
	unique_ptr<Animator> m_animator;
	sf::Clock m_woodClock;
};

