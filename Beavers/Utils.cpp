#include "Utils.h"

Vec2f normalize(Vec2f& _vec2)
{
	float fMagnitude = Length(_vec2);
	if (fMagnitude == 0.0f) return Vec2f(0.0f, 0.0f);
	return _vec2 /= fMagnitude;
}

float Length(Vec2f& _vec2)
{
	return sqrtf(powf(_vec2.x, 2) + powf(_vec2.y, 2));
}
