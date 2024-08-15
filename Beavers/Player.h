#pragma once
#include "Object.h"
#include "ControlScheme.h"

class Player : public Object
{
public:
	Player(Vec2f _position, shared_ptr<b2World> _world);
	
	void Update(float _fDeltaTime) override;
	void SetControlScheme(ControlScheme _scheme);

private:
	sf::Clock m_animationClock;
	float m_fSpeed = 15.0f;

	int m_iAnimationFrame = 0;
	
	ControlScheme m_controlScheme;
};

