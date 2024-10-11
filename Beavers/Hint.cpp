#include "Hint.h"
#include "Player.h"
#include <iostream>

Hint::Hint(Vec2f _position, weak_ptr<b2World> _sceneWorld) : Object(_position, "Resources/Objects/Warehouse.png", _sceneWorld, true)
{
	//m_hintText = make_unique<Text>((Vec2f(640, 360) / 2.0f + Vec2f(0.0f, 150.0f), "yoza", "Resources/Fonts/Yogurt Extra.ttf"));
	
	int m_iCost = 1;
	m_hintText = make_unique<Text>(Vec2f(_position), "hai", "Resources/Fonts/Yogurt Extra.ttf");
}

void Hint::SetText(std::string _strText)
{
	m_hintText->SetText(_strText);
}

void Hint::Render(sf::RenderTexture* _sceneBuffer)
{
	//Object::Render(_sceneBuffer);
	//m_statUI->Render(_sceneBuffer);

	m_hintText->Render(_sceneBuffer);
}
