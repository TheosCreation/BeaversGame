#pragma once
#include "TextureManager.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Window/Event.hpp"

class GameObject
{
public:
	GameObject() = default;
	~GameObject() = default;

	// Position Methods
	virtual void SetPosition(Vector2f _newPosition) abstract;
	virtual void AddPosition(Vector2f _displacement) abstract;
	virtual Vector2f GetPosition() abstract;

	// Render Methods
	void SetVisibility(bool _bIsVisible);
	virtual void Render(sf::RenderTexture* _sceneBuffer) abstract;

	// Mouse Methods
	virtual void OnClick(Vector2f _mousePos);
	virtual void OnDrag(Vector2f _mousePos);
	virtual void OnRelease(Vector2f _mousePos);

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
	static inline sf::Window* m_window = nullptr;

	bool m_bIsVisible = true;
	bool m_bIsActive = true;
};

