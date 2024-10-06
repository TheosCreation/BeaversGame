#include "Utils.h"

Vec2f normalize(Vec2f& _vec2f)
{
	float fMagnitude = sqrtf(powf(_vec2f.x, 2) + powf(_vec2f.y, 2));
	if (fMagnitude == 0.0f) return Vec2f(0.0f, 0.0f);
	return _vec2f /= fMagnitude;
}
