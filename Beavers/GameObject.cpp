#include "GameObject.h"

/*
	Interface for Click Events

	@author Jamuel Bocacao
	@param Vec2f: Mouse Position in World-Space
*/
void GameObject::OnClick(Vec2f _mousePos)
{
	return;
}

/*
	Interface for Drag Events

	@author Jamuel Bocacao
	@param Vec2f: Mouse Position in World-Space
*/
void GameObject::OnDrag(Vec2f _mousePos)
{
	return;
}

/*
	Interface for Release Events

	@author Jamuel Bocacao
	@param Vec2f: Mouse Position in World-Space
*/
void GameObject::OnRelease(Vec2f _mousePos)
{
	return;
}

/*
	Interface for Begin Contact Events

	@author Jamuel Bocacao
	@param GameObject*: Other object in contact with
*/
void GameObject::OnBeginContact(GameObject* _otherObject)
{
	return;
}

/*
	Interface for End Contact Events

	@author Jamuel Bocacao
	@param GameObject*: Other object in contact with
*/
void GameObject::OnEndContact(GameObject* _otherObject)
{
	return;
}

/*
	Draws sprite to View Buffer

	@author Jamuel Bocacao
	@param sf::RenderTexture*: Scene's View Buffer
	@param sf::Sprite: Sprite to be drawn
*/
void GameObject::DrawSprite(sf::RenderTexture* _sceneBuffer, sf::Sprite& _sprite)
{
	_sceneBuffer->draw(_sprite);
	_sceneBuffer->display();
}

/*
	Sets the Visibility of the Game Object

	@author Jamuel Bocacao
	@param bool: Whether GameObject will be rendered
*/
void GameObject::SetVisibility(bool _bIsVisible)
{
	m_bIsVisible = _bIsVisible;
}

/*
	Sets whether Game Object should be simulated

	@author Jamuel Bocacao
	@param bool: Whether Game Object is simulated
*/
void GameObject::SetActive(bool _bIsActive)
{
	m_bIsActive = _bIsActive;
}