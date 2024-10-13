#include "TileMap.h"

TileMap::TileMap(Vec2u _mapSize, Vec2f _tileSize)
    : m_mapSize(_mapSize), m_tileSize(_tileSize)
{
    m_tiles.resize(m_mapSize.y, vector<shared_ptr<Tile>>(m_mapSize.x, nullptr));
}

void TileMap::SetTile(Vec2u _position, shared_ptr<Tile> _tile)
{
    if (_position.x < m_mapSize.x && _position.y < m_mapSize.y)
    {
        m_tiles[_position.y][_position.x] = _tile;
        if (_tile)
        {
            _tile->SetPosition(Vec2f(m_position.x + _position.x * m_tileSize.x + m_tileSize.x / 2,
                m_position.y + _position.y * m_tileSize.y + m_tileSize.y / 2));
        }
    }
}

void TileMap::SetPosition(Vec2f _newPosition)
{
    Vec2f displacement = _newPosition - m_position;
    AddPosition(displacement);
}

void TileMap::AddPosition(Vec2f _displacement)
{
    m_position += _displacement;
    for (size_t y = 0; y < m_mapSize.y; ++y)
    {
        for (size_t x = 0; x < m_mapSize.x; ++x)
        {
            if (m_tiles[y][x])
            {
                m_tiles[y][x]->AddPosition(_displacement);
            }
        }
    }
}

Vec2f TileMap::GetPosition()
{
    return m_position;
}

void TileMap::Render(sf::RenderTexture* _sceneBuffer)
{
    for (const auto& row : m_tiles)
    {
        for (const auto& tile : row)
        {
            if (tile)
            {
                tile->Render(_sceneBuffer);
            }
        }
    }
}
