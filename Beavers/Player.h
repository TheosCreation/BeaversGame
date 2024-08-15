#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player(Vec2f _position, shared_ptr<b2World> _world);
};

