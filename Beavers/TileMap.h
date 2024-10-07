#pragma once
#include "GameObject.h"
#include "Tile.h"
#include <vector>

class TileMap : public GameObject
{
public:
    TileMap(Vec2u _mapSize, Vec2f _tileSize);

    void SetTile(Vec2u _position, shared_ptr<Tile> _tile);
    void SetPosition(Vec2f _newPosition) override;
    void AddPosition(Vec2f _displacement) override;
    Vec2f GetPosition() override;
    void Render(sf::RenderTexture* _sceneBuffer) override;

private:
    Vec2u m_mapSize;
    Vec2f m_tileSize;
    Vec2f m_position;
    vector<vector<shared_ptr<Tile>>> m_tiles;
};
