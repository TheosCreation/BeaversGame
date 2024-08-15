#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player(Vec2f _position, shared_ptr<b2World> _world);
	
	void Update(float _fDeltaTime) override;

private:
	sf::Clock m_animationClock;
	float m_fSpeed = 30.0f;

	int m_iAnimationFrame = 0;
};

