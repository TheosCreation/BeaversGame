#pragma once
#include "Object.h"
class Tree : public Object
{
public:
	Tree(Vec2f _position, weak_ptr<b2World> _sceneWorld);
};

