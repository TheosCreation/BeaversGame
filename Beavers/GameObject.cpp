#include "GameObject.h"

/*
	Interface for Click Events

	@author Jamuel Bocacao
	@param Vec2f: Mouse Position in World-Space
	@return bool: Clicked on Element
*/
bool GameObject::OnClick(Vec2f _mousePos)
{
	return false;
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
	Interface for Updating Objects

	@author Jamuel Bocacao
	@param float: Delta Time
*/
void GameObject::Update(float _fDeltaTime)
{
	return;
}

/*
	Adds a child to this game object

	@author Theo Morris
	@param shared_ptr<GameObject>: The child ptr to add as a child to this game object
*/
void GameObject::AddChild(shared_ptr<GameObject> _child)
{
	m_children.push_back(_child);
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

	@author Jamuel Bocacao and Theo Morris
	@param bool: Whether GameObject will be rendered
*/
void GameObject::SetVisibility(bool _bIsVisible)
{
	m_bIsVisible = _bIsVisible;
	for (auto& child : m_children)
	{
		child->SetVisibility(m_bIsVisible);
	}
}

/*
	Interface for Rendering Object

	@author Jamuel Bocacao
	@param sf::RenderTexture*: Scene's View Buffer
*/
void GameObject::Render(sf::RenderTexture* _sceneBuffer)
{
	return;
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

/*
	Marks Game Object for Destruction

	@author Jamuel Bocacao
*/
void GameObject::Destroy()
{
	m_bDestroyed = true;
}

/*
	Checks to see if Game Object is marked for destruction

	@author Jamuel Bocacao
*/
bool GameObject::MarkedForDestroy()
{
	return m_bDestroyed;
}