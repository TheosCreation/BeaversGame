#include "Tree.h"

/*
	Creates a Tree Object

	@author(s) Jamuel Bocacao
	@param Vec2f: Position of Tree
*/
Tree::Tree(Vec2f _position) : Object(_position, "Resources/Objects/Tree.png", true)
{
	m_sprite.setOrigin(32, 116);
	AddBoxCollider(Vec2f(0, 7), Vec2f(10, 7));
}
