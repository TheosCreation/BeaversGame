#include "Text.h"
#include "FontManager.h"

/*
	Creates a Text Object

	@author Jamuel Bocacao
	@param Vec2f: Position of Text
	@param string: Text String of Text Object
	@param string: Font File Path
*/
Text::Text(Vec2f _position, string _strText, string _strFontPath)
{
	SetPosition(_position);
	SetText(_strText);
	SetFont(_strFontPath);
}

/*
	Set's Text's string

	@author Jamuel Bocacao
	@param string: New Text
*/
void Text::SetText(string _strText)
{
	m_text.setString(_strText);
	m_bUpdateText = true;
}

/*
	Sets Text's Font

	@author Jamuel Bocacao
	@param string: Font File Path
*/
void Text::SetFont(string _strFontPath)
{
	m_text.setFont(FontManager::GetInstance().GetFont(_strFontPath));
	m_bUpdateText = true;
}

/*
	Sets Size of Characters

	@author Jamuel Bocacao
	@param unsigned int: Size of Characters in Pixels
*/
void Text::SetSize(unsigned int _iFontSize)
{
	m_text.setCharacterSize(_iFontSize);
	m_bUpdateText = true;
}

/*
	Sets Colour of Text

	@author Jamuel Bocacao
	@param sf::Color: Color Data
*/
void Text::SetColour(sf::Color _color)
{
	m_text.setFillColor(_color);
}

/*
	Sets Position of Text

	@author Jamuel Bocacao
	@param Vec2f: New Position of Text
*/
void Text::SetPosition(Vec2f _newPosition)
{
	m_text.setPosition(_newPosition);
}

/*
	Displaces the Text's Position

	@author Jamuel Bocacao
	@param Vec2f: Displacement Vector
*/
void Text::AddPosition(Vec2f _displacement)
{
	m_text.setPosition(m_text.getPosition() + _displacement);
}

/*
	Gets the Text's Position

	@author Jamuel Bocacao
	@return Vec2f: Text's World Position
*/
Vec2f Text::GetPosition()
{
	return m_text.getPosition();
}

/*
	Renders Text to Scene Buffer

	@author Jamuel Bocacao
	@param sf::RenderTexture*: Scene's View Buffer
*/
void Text::Render(sf::RenderTexture* _sceneBuffer)
{
	// Check if Text size has been updated
	if (m_bUpdateText)
	{
		// Centre Text again
		auto texRect = m_text.getLocalBounds();
		m_text.setOrigin(texRect.width / 2.0f, texRect.height / 2.0f);
		m_bUpdateText = false;
	}

	// Render Text
	_sceneBuffer->draw(m_text);
	_sceneBuffer->display();
}
