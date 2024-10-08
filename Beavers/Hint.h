#pragma once
#include "Object.h"
#include "PlayerStats.h"
#include "Image.h"
#include "Warehouse.h"
#include "Text.h"

enum class hintText
{
	Forest,
	Shop,
	Warehouse
};

class Hint : public Text
{
public:
	Hint(Vec2f _position, weak_ptr<b2World> _sceneWorld);

	void SetHintType(hintText _hintType);

	virtual void Render(sf::RenderTexture* _sceneBuffer) override;

private:
	hintText m_hintType;
};