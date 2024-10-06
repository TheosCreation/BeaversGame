#pragma once
#include "Object.h"
#include "Utils.h"

class Tile : public Object
{
	Tile(Vec2i _gridPos, string _strTexPath, bool _bCollidable = true);
};

