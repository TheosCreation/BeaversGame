#include "FlowField.h"
#include <queue>

using std::queue;

FlowField::FlowField(Vec2i _topLeftGrid, Vec2i _bottomRightGrid, unsigned int _iGridSize)
{
	m_topLeft = _topLeftGrid;
	m_iGridSize = _iGridSize;

	m_size = (_bottomRightGrid - _topLeftGrid);
	int iWidth = m_size.x;
	int iHeight = m_size.y;

	m_field.resize(iWidth * iHeight, Vec2f(1, 1));
}

void FlowField::SetWalkable(Vec2i _gridPos, bool _bWalkable)
{
	if (!IsValid(_gridPos)) return;
	Vec2i vectorPos = _gridPos - m_topLeft;
	m_field[vectorPos.y * m_size.x + vectorPos.x] = (_bWalkable) ? Vec2f(1, 1) : Vec2f(0, 0);
}

Vec2f FlowField::GetCellValue(Vec2f _worldPos)
{
	return GetValue(GetCellPos(_worldPos));
}

Vec2i FlowField::GetCellPos(Vec2f _worldPos)
{
	return Vec2i(_worldPos /= float(m_iGridSize)) - m_topLeft;
}

Vec2f FlowField::GetValue(Vec2i _gridPos)
{
	if (!IsValid(_gridPos)) return Vec2f(0, 0);
	Vec2i vectorPos = _gridPos - m_topLeft;
	return m_field[vectorPos.y * m_size.x + vectorPos.x];
}

void FlowField::CalculateField(vector<Vec2i>& _startPositions)
{
	vector<float> gridValue;
	vector<bool> visitedCells;
	queue<Vec2i> openCells;

	gridValue.resize(m_size.x * m_size.y, 0);
	visitedCells.resize(m_size.x * m_size.y, false);

	// Add Start Points to Queue
	for (auto pos : _startPositions)
	{
		Vec2i cellPos = pos - m_topLeft;
		if (IsValid(cellPos) && IsWalkable(cellPos))
		{
			openCells.push(cellPos);
			visitedCells[cellPos.y * m_size.x + cellPos.x] = true;
		}
	}

	if (openCells.empty()) return;

	// Create Field Heat Map
	while (!openCells.empty())
	{
		auto cell = openCells.front();
		// Iterate through Neighbor Cells
		for (int y = -1; y <= 1; y++)
		{
			for (int x = -1; x <= 1; x++)
			{
				// Skip if Current Cell
				if (x == 0 && y == 0) continue;

				// Check if Neighbor is valid and walkable
				auto neighbor = cell + Vec2i(x, y);
				if (!IsValid(neighbor)) continue;
				if (!IsWalkable(neighbor))
				{
					gridValue[neighbor.y * m_size.x + neighbor.x] = -1;
					continue;
				}

				// Process Neighbors
				float fDistCell = gridValue[cell.y * m_size.x + cell.x];

				// Check if Neighbor cell has already been visited
				if (!visitedCells[neighbor.y * m_size.x + neighbor.x])
				{
					// Calculate Distance of Neighbor to Goal 
					gridValue[neighbor.y * m_size.x + neighbor.x] = fDistCell + 1;
					openCells.push(neighbor);
					visitedCells[neighbor.y * m_size.x + neighbor.x] = true;
				}
				else
				{
					// Check if Shorter Distance is Found
					float fDistNeighbor = gridValue[neighbor.y * m_size.x + neighbor.x];
					if (fDistNeighbor > fDistCell + 1)
					{
						gridValue[neighbor.y * m_size.x + neighbor.x] = fDistCell + 1;
					}
				}
			}
		}
		openCells.pop();
	}


	// Convolute Field
	for (int y = 0; y < m_size.y; y++)
	{
		for (int x = 0; x < m_size.x; x++)
		{
			Vec2i cell(x, y);
			cell -= m_topLeft;
			if (!IsWalkable(cell) || gridValue[cell.y * m_size.x + cell.x] == 0.0f)
			{
				m_field[y * m_size.x + x] = Vec2f(0, 0);
				continue;
			}

			// Check if Cell has Neighboring Wall
			bool bNeighboringWall = false;
			for (int dy = -1; dy <= 1 && !bNeighboringWall; dy++)
			{
				if (y + dy < 0 || y + dy >= m_size.y) continue;
				for (int dx = -1; dx <= 1 ; dx++)
				{
					if (x + dx < 0 || x + dx >= m_size.x) continue;
					if (gridValue[(y + dy) * m_size.x + (x + dx)] == -1)
					{
						bNeighboringWall = true;
						break;
					}
				}
			}
					
			// Process Cell
			Vec2f cellVector;
			// If Cell has a Wall as a Neighbor, use the non-wall neighboring cell that has the lowest value
			if (bNeighboringWall)
			{
				float fMinCellValue = FLT_MAX;
				// Check which valid cell has the lowest value
				// Process Neighbor Cells
				for (int dy = -1; dy <= 1; dy++)
				{
					if (y + dy < 0 || y + dy >= m_size.y) continue;
					for (int dx = -1; dx <= 1; dx++)
					{
						if (x + dx < 0 || x + dx >= m_size.x) continue;

						// Get Value
						float fCellValue = gridValue[(y + dy) * m_size.x + (x + dx)];
						if (fCellValue == -1) continue;	// Ignore Wall
						if (fCellValue < fMinCellValue)	// Check if Lowest Value
						{
							cellVector = Vec2f(float(dx), float(dy)); // Set Direction of Cell
							fMinCellValue = fCellValue;
						}
					}
				}
			}
			// Use Kernel Convolution instead to average out Field Values
			else
			{
				// Process Neighbor Cells
				for (int dy = -1; dy <= 1; dy++)
				{
					if (y + dy < 0 || y + dy >= m_size.y) continue;
					for (int dx = -1; dx <= 1; dx++)
					{
						if (x + dx < 0 || x + dx >= m_size.x) continue;
						// Get Neighbor Vector
						Vec2f neighborVector((float)dx, (float)dy);
						neighborVector = normalize(neighborVector);

						// Reduce Neighbor Vector proportional to distance to Goal
						float cellValue = gridValue[(y + dy) * m_size.x + (x + dx)];
						if (cellValue > 0)
						{
							neighborVector /= cellValue;
						}
						// Add Vector to Average Direction if Neighbor is not Wall
						if (cellValue >= 0)
						{
							cellVector += neighborVector;
						}
					}
				}
			}
			
			// Update Field Value
			m_field[y * m_size.x + x] = normalize(cellVector);
		}
	}
}

/*
void FlowField::Render(sf::RenderTexture* _texture)
{
	sf::ConvexShape shape;
	shape.setPointCount(7);
	shape.setPoint(0, Vec2f(32, 0));
	shape.setPoint(1, Vec2f(64, 32));
	shape.setPoint(2, Vec2f(32, 64));
	shape.setPoint(3, Vec2f(32, 44));
	shape.setPoint(4, Vec2f(0, 44));
	shape.setPoint(5, Vec2f(0, 20));
	shape.setPoint(6, Vec2f(32, 20));
	
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(32.0f, 32.0f);
	for (int i = 0; i < m_size.y; i++)
	{
		for (int j = 0; j < m_size.x; j++)
		{
			Vec2f dir = m_field[i * m_size.x + j];
			if (dir == Vec2f(0, 0))
			{
				sf::RectangleShape rect;
				rect.setSize(Vec2f(64.0f, 64.0f));
				rect.setOrigin(32, 32);
				rect.setFillColor(sf::Color::Red);
				rect.setPosition(Vec2f(j * 64.0f + 32, i * 64.0f + 32));
				_texture->draw(rect);
				_texture->display();
				continue;
			}

			float angle = atan2(dir.y, dir.x) * (180.0f / 3.141592653589793238463f);
			
			
			shape.setRotation(angle);
			shape.setPosition(Vec2f(j * 64.0f + 32, i * 64.0f + 32));

			_texture->draw(shape);
			_texture->display();
		}
	}
}
*/


bool FlowField::IsWalkable(Vec2i _gridPos)
{
	if (!IsValid(_gridPos)) return false;
	if (GetValue(_gridPos) == Vec2f(0, 0)) return false;
	return true;
}

bool FlowField::IsValid(Vec2i _gridPos)
{
	Vec2i vectorPos = _gridPos - m_topLeft;
	if (vectorPos.x < 0 || vectorPos.y < 0) return false;
	if (vectorPos.x >= m_size.x || vectorPos.y >= m_size.y) return false;
	return true;
}
