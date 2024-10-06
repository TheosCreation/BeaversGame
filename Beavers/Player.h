#pragma once
#include "Object.h"
#include "ControlScheme.h"
#include "Event.h"
#include "Shop.h"
#include "PlayerStats.h"
#include "Animator.h"

class Player : public Object
{
public:
	Player(Vec2f _position);
	
	void Update(float _fDeltaTime) override;
	void SetControlScheme(ControlScheme _scheme);
	
	// Wood Amount Methods
	void SetWoodAmountChangeEvent(shared_ptr<Event2P<void, shared_ptr<GameObject>, int>> _woodAmountChangeEvent);
	void ExecuteWoodAmountChangeEvent(int _iAmount);

	void OnBeginContact(Object* _other) override;
	void OnEndContact(Object* _other) override;
	
	void SetShopRef(Shop* _shop);

	int Deposit();

private:
	static PlayerStats m_playerStats;

	unique_ptr<Animator> m_animator;
	sf::Clock m_interactClock;
	int m_iAnimationFrame = 0;

	float m_fSpeed = 50.0f;

	int m_iWoodAmount = 50;
	
	ControlScheme m_controlScheme;

	bool m_bNearTree = false;
	bool m_bInteracting = false;

	shared_ptr<Event2P<void, shared_ptr<GameObject>, int>> m_woodAmountChangeEvent;

	Shop* m_shopRef = nullptr;
};

inline PlayerStats Player::m_playerStats;