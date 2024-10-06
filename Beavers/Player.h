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
	Player(Vec2f _position, weak_ptr<b2World> _world);
	
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
	bool m_bHintVisible = false;

	bool m_bHintOnce = false;

	bool hintKeyWasPressed = false;

	shared_ptr<Event2P<void, shared_ptr<GameObject>, int>> m_woodAmountChangeEvent;

	Shop* m_shopRef = nullptr;

	Text* m_HintRef = nullptr;

	enum class hintText
	{
		None,
		Forest,
		Shop,
		Warehouse
	};

	// Variable to track the last hint displayed
	hintText previousHint = hintText::None;
	hintText currentHint = hintText::None;
};

inline PlayerStats Player::m_playerStats;