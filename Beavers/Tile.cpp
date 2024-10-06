#include "Tile.h"

/*
	Creates a Tile Object

	@author Jamuel Bocacao
	@param Vec2i: Position of Tile in Tilemap
	@param string: File Path of Tile's Texture
	@param bool: Tile can be collided with
*/
Tile::Tile(Vec2i _gridPos, string _strTexPath, bool _bCollidable) : Object(Vec2f(_gridPos * TileSize), _strTexPath, true)
{
	if (_bCollidable)
	{
		AddBoxCollider(Vec2f(0, 0), Vec2f(TileSize, TileSize));
	}
}
