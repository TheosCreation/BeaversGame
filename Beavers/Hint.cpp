#include "Hint.h"
#include "Player.h"
#include <iostream>

Hint::Hint(Vec2f _position, weak_ptr<b2World> _sceneWorld) : Text(_position, "No Hints", "Resources/Fonts/Yogurt Extra.ttf")
{

}

void Hint::SetHintType(hintText _hintType)
{
	//m_hintType = _hintType;
	//switch (m_hintType)
	//{
	//case hintText::Forest:
	//	_strText = "Press E to chop wood";
	//	break;
	//case hintText::Shop:
	//	_strText = "Press E to open shop";
	//	break;
	//case hintText::Warehouse:
	//	_strText = "Press E to open warehouse";
	//	break;
	//}
}

void Hint::Render(sf::RenderTexture* _sceneBuffer)
{
}
