#pragma once
#include "GameObject.h"

const int GridSize = 64;

class FlowField : public GameObject
{
public:
	FlowField(Vec2i _topLeftGrid, Vec2i _bottomRightGrid);

	void SetWalkable(Vec2i _gridPos, bool _bWalkable);

	void SetPosition(Vec2f _pos) override;
	void AddPosition(Vec2f _pos) override;
	Vec2f GetPosition() override;

	Vec2f GetValue(Vec2i _gridPos);

	void CalculateField(vector<Vec2i>& _startPositions);

	void Render(sf::RenderTexture* _texture) override;

private:
	bool IsWalkable(Vec2i _gridPos);
	bool IsValid(Vec2i _gridPos);


private:
	Vec2i m_topLeft;
	Vec2i m_size;
	vector<Vec2f> m_field;
};

