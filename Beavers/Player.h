#pragma once
#include "Object.h"
#include "ControlScheme.h"

class Player : public Object
{
public:
	Player(Vec2f _position, weak_ptr<b2World> _world);
	
	void Update(float _fDeltaTime) override;
	void SetControlScheme(ControlScheme _scheme);

	int Deposit();

private:
	sf::Clock m_animationClock;
	int m_iAnimationFrame = 0;

	float m_fSpeed = 60.0f;

	int m_iWoodAmount = 50;
	
	ControlScheme m_controlScheme;
};

