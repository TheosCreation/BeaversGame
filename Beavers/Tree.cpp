#include "Tree.h"

/*
	Creates a Tree Object

	@author(s) Jamuel Bocacao
	@param Vec2f: Position of Tree
	@param weak_ptr<b2World>: Scene World
*/
Tree::Tree(Vec2f _position, weak_ptr<b2World> _sceneWorld) : Object(_position, "Resoureces/Images/Objects/Tree.png", _sceneWorld, true)
{
}
