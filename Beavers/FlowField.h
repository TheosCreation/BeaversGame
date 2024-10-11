#pragma once
#include "GameObject.h"

const int GridSize = 64;

class FlowField
{
public:
	FlowField(Vec2i _topLeftGrid, Vec2i _bottomRightGrid, unsigned int _iGridSize);

	void SetWalkable(Vec2i _gridPos, bool _bWalkable);

	Vec2f GetCellValue(Vec2f _worldPos);
	Vec2f GetValue(Vec2i _gridPos);

	void CalculateField(vector<Vec2i>& _startPositions);

private:
	bool IsWalkable(Vec2i _gridPos);
	bool IsValid(Vec2i _gridPos);

private:
	Vec2i m_topLeft;
	Vec2i m_size;
	int m_iGridSize;
	vector<Vec2f> m_field;
};

