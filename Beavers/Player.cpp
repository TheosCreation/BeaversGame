#include "Player.h"

Player::Player(Vec2f _position, shared_ptr<b2World> _world) : Object(_position, "Resources/Images/Entities/Player.png", _world, false)
{
	SetDrawRect(sf::IntRect(0, 0, 16, 16));
	AddBoxCollider(Vec2f(0, 6), Vec2f(16, 2), false);
}
