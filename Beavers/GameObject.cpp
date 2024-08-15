#include "GameObject.h"
#include "SFML/Graphics/RenderTexture.hpp"

/*
	Interface for Click Events

	@author Jamuel Bocacao
	@param Vector2f: Mouse Position in World-Space
*/
void GameObject::OnClick(Vector2f _mousePos)
{
	return;
}

/*
	Interface for Drag Events

	@author Jamuel Bocacao
	@param Vector2f: Mouse Position in World-Space
*/
void GameObject::OnDrag(Vector2f _mousePos)
{
	return;
}

/*
	Interface for Release Events

	@author Jamuel Bocacao
	@param Vector2f: Mouse Position in World-Space
*/
void GameObject::OnRelease(Vector2f _mousePos)
{
	return;
}

/*
	Interface for Key Press Events

	@author Jamuel Bocacao
	@param sf::Event&: Event Handle
*/
void GameObject::OnKeyDown(sf::Event& _event)
{
	return;
}

/*
	Interface for Key Release Events

	@author Jamuel Bocacao
	@param sf::Event&: Event Handle
*/
void GameObject::OnKeyUp(sf::Event& _event)
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
	Interface for Updating Objects

	@author Jamuel Bocacao
	@param float: Delta Time
*/
void GameObject::Update(float _fDeltaTime)
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