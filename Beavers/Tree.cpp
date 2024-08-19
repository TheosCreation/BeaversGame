#include "Tree.h"

/*
	Creates a Tree Object

	@author(s) Jamuel Bocacao
	@param Vec2f: Position of Tree
	@param weak_ptr<b2World>: Scene World
*/
Tree::Tree(Vec2f _position, weak_ptr<b2World> _sceneWorld) : Object(_position, "Resources/Images/Objects/Tree.png", _sceneWorld, true)
{
	m_sprite.setOrigin(32, 116);
	AddBoxCollider(Vec2f(0, 7), Vec2f(10, 7));
}
