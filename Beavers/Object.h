#pragma once
#include "GameObject.h"
#include <Box2D/box2d.h>

#define PixelsPerMeter 64.0f

class Object : public GameObject
{
public:
	Object(Vec2f _position, string _strTexturePath, weak_ptr<b2World> _sceneWorld, bool _bIsStatic = false);
	~Object();

	// Position Methods
	void SetPosition(Vec2f _newPosition) override;
	void AddPosition(Vec2f _displacement) override;
	virtual Vec2f GetPosition() override;

	// Physics Methods
	void ApplyForce(Vec2f _force);

	// Collider Methods
	void AddBoxCollider(Vec2f _relativePosition, Vec2f _size, bool _bIsTrigger = false);
	void AddCircleCollider(Vec2f _relativePosition, float _fRadius, bool _bIsTrigger = false);

	// Texture Methods
	void SetTexture(string _strTexturePath);
	void SetDrawRect(sf::IntRect _drawRect);
	const sf::Texture* GetTexture() const;

	// Render Methods
	virtual void Render(sf::RenderTexture* _sceneBuffer) override;

protected:
	sf::Sprite m_sprite;

	weak_ptr<b2World> m_world;
	b2Body* m_body;
};