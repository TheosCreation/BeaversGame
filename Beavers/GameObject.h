#pragma once
#include "TextureManager.h"

typedef sf::Vector2f Vec2f;
typedef sf::Vector2i Vec2i;
typedef sf::Vector2u Vec2u;

class GameObject
{
public:
	GameObject() = default;
	~GameObject() = default;

	// Position Methods
	virtual void SetPosition(Vec2f _newPosition) abstract;
	virtual void AddPosition(Vec2f _displacement) abstract;
	virtual Vec2f GetPosition() abstract;

	// Render Methods
	void SetVisibility(bool _bIsVisible);
	virtual void Render(sf::RenderTexture* _sceneBuffer);

	// Mouse Methods
	virtual void OnClick(Vec2f _mousePos);
	virtual void OnDrag(Vec2f _mousePos);
	virtual void OnRelease(Vec2f _mousePos);

	// Keyboard Methods
	virtual void OnKeyDown(sf::Event& _event);
	virtual void OnKeyUp(sf::Event& _event);

	// Collision Methods
	virtual void OnBeginContact(GameObject* _otherObject);
	virtual void OnEndContact(GameObject* _otherObject);

	// Update Methods
	virtual void Update(float _fDeltaTime);

	// Simulation Methods
	void SetActive(bool _bIsActive);


protected:
	static void DrawSprite(sf::RenderTexture* _sceneBuffer, sf::Sprite& _sprite);

	bool m_bIsVisible = true;
	bool m_bIsActive = true;
};

