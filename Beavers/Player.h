#pragma once
#include "Object.h"
#include "ControlScheme.h"
#include "Event.h"

class Player : public Object
{
public:
	Player(Vec2f _position, weak_ptr<b2World> _world);
	
	void Update(float _fDeltaTime) override;
	void SetControlScheme(ControlScheme _scheme);
	
	// Wood Amount Methods
	void SetWoodAmountChangeEvent(shared_ptr<Event2P<void, shared_ptr<GameObject>, int>> _woodAmountChangeEvent);
	void ExecuteWoodAmountChangeEvent(int _iAmount);

	int Deposit();

private:
	sf::Clock m_animationClock;
	int m_iAnimationFrame = 0;

	float m_fSpeed = 40.0f;

	int m_iWoodAmount = 50;
	
	ControlScheme m_controlScheme;

	shared_ptr<Event2P<void, shared_ptr<GameObject>, int>> m_woodAmountChangeEvent;
};

