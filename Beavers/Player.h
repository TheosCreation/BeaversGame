#pragma once
#include "Object.h"
#include "ControlScheme.h"
#include "Event.h"
#include "Shop.h"
#include "PlayerStats.h"

class Player : public Object
{
public:
	Player(Vec2f _position, weak_ptr<b2World> _world);
	
	void Update(float _fDeltaTime) override;
	void SetControlScheme(ControlScheme _scheme);
	
	// Wood Amount Methods
	void SetWoodAmountChangeEvent(shared_ptr<Event<void, shared_ptr<GameObject>>> _woodAmountChangeEvent);
	void ExecuteWoodAmountChangeEvent(int _iAmount);

	void SetShopRef(Shop* _shop);

	int Deposit();

private:
	static PlayerStats m_playerStats;

	sf::Clock m_animationClock;
	int m_iAnimationFrame = 0;

	float m_fSpeed = 40.0f;

	int m_iWoodAmount = 50;
	
	ControlScheme m_controlScheme;

	shared_ptr<Event<void, shared_ptr<GameObject>>> m_woodAmountChangeEvent;

	Shop* m_shopRef = nullptr;
};

inline PlayerStats Player::m_playerStats;