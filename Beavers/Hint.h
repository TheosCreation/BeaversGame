#pragma once
#include "Object.h"
#include "PlayerStats.h"
#include "Image.h"
#include "Warehouse.h"
#include "Text.h"

enum class HintType
{
	None,
	Forest,
	Shop,
	Warehouse
};

//maybe make this a wrapper to the Text class instead instead of containing all the physics stuff and also having a text member
class Hint : public Object
{
public:
	Hint(Vec2f _position);

	void SetText(std::string _strText);

	virtual void Render(sf::RenderTexture* _sceneBuffer) override;
	virtual void SetPosition(Vec2f _newPosition) override;


private:
	//HintType m_hintType; //Unused remove

	unique_ptr<Text> m_hintText;
};