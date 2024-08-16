#include "Shop.h"

/*
	Creates a Shop Object

	@author(s) Jamuel Bocacao
	@param Vec2f: Position of Shop
	@param weak_ptr<b2World>: Scene World
*/
Shop::Shop(Vec2f _position, weak_ptr<b2World> _sceneWorld) : Object(_position, "Resources/Images/Objects/Shop.png", _sceneWorld, true)
{
}
