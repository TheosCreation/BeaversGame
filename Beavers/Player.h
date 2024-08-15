#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player(Vec2f _position, shared_ptr<b2World> _world);

	void Move(Vec2f _moveDir, float _fDeltaTime);
	void Update(float _fDeltaTime) override;

private:
	float m_fSpeed = 30.0f;
};

