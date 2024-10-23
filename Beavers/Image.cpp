#include "Image.h"

/*
	Creates an Image

	@author Jamuel Bocacao
	@param string: Texture File Path
*/
Image::Image(string _strTexturePath)
{
	SetTexture(_strTexturePath);
}

/*
	Creates an Image

	@author Jamuel Bocacao
	@param Vec2f: Position of Button
	@param string: Texture File Path
*/
Image::Image(Vec2f _position, string _strTexturePath)
{
	SetPosition(_position);
	SetTexture(_strTexturePath);
}

/*
	Sets the Image's Position

	@author Jamuel Bocacao
	@param Vec2f: New Position of Image
*/
void Image::SetPosition(Vec2f _newPosition)
{
	m_sprite.setPosition(_newPosition);
}

/*
	Displaces the Image's Position

	@author Jamuel Bocacao
	@param Vec2f: Displacement Vector
*/
void Image::AddPosition(Vec2f _displacement)
{
	auto position = m_sprite.getPosition();
	m_sprite.setPosition(position + _displacement);
}

/*
	Gets the Image's Position

	@author Jamuel Bocacao
	@return Vec2f: Position of Image
*/
Vec2f Image::GetPosition()
{
	return m_sprite.getPosition();
}

/*
	Sets the Image's Texture

	@author Jamuel Bocacao
	@param Vec2f: New Position of Image
*/
void Image::SetTexture(string _strTexturePath)
{
	m_sprite.setTexture(TextureManager::GetInstance().GetTexture(_strTexturePath), true);
	auto texRect = m_sprite.getLocalBounds();
	m_sprite.setOrigin(texRect.width / 2.0f, texRect.height / 2.0f);
}

/*
	Gets the Image's Texture

	@author Jamuel Bocacao
	@return sf::Texture*: Image's Texture Handle
*/
const sf::Texture* Image::GetTexture() const
{
	return m_sprite.getTexture();
}

/*
	Gets the Image's Bounding Box

	@author Jamuel Bocacao
	@return sf::FloatRect Image's World-Space Bounding Box
*/
sf::FloatRect Image::GetBounds()
{
	return m_sprite.getGlobalBounds();
}

/*
	Renders Image to Scene View Buffer

	@author Jamuel Bocacao and Theo Morris
	@param sf::RenderTexture*: Scene View Buffer 
*/
void Image::Render(sf::RenderTexture* _sceneBuffer)
{
	if (m_bIsVisible)
	{
		DrawSprite(_sceneBuffer, m_sprite);
	}
}
