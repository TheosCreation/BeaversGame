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

class Hint : public Object
{
public:
	Hint(Vec2f _position, weak_ptr<b2World> _sceneWorld);

	void SetText(std::string _strText);

	virtual void Render(sf::RenderTexture* _sceneBuffer) override;


private:
	hintText m_hintType;

	unique_ptr<Text> m_hintText;
};