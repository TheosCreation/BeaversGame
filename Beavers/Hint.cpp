#include "Hint.h"
#include "Player.h"
#include <iostream>

/*
	Creates a Hint

	@author Theo Morris and Nick
	@param Vec2f: Position for the text on screen initialy
*/
Hint::Hint(Vec2f _position) : Object(_position, "Resources/Objects/Warehouse.png", true) //look at this unused contructor so useless
{
	//m_hintText = make_unique<Text>((Vec2f(640, 360) / 2.0f + Vec2f(0.0f, 150.0f), "yoza", "Resources/Fonts/Yogurt Extra.ttf"));
	
	int m_iCost = 1;
	m_hintText = make_unique<Text>(Vec2f(_position), "", "Resources/Fonts/AlteHaasGroteskBold.ttf");
	m_hintText->SetSize(12);
}

/*
	Sets the position of the text

	@author Nick
*/
void Hint::SetText(std::string _strText)
{
	m_hintText->SetText(_strText);
}

/*
	Renders the text

	@author Nick
	@param sf::RenderTexture*: Scene View Buffer 
*/
void Hint::Render(sf::RenderTexture* _sceneBuffer)
{
	//Object::Render(_sceneBuffer);
	m_hintText->Render(_sceneBuffer);
}

/*
	Sets the position of the text

	@author Theo Morris
*/
void Hint::SetPosition(Vec2f _newPosition)
{
	m_hintText->SetPosition(_newPosition);
}
