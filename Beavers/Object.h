#pragma once
#include "GameObject.h"
#include <Box2D/box2d.h>

#define PixelsPerMeter 64.0f

class Object : public GameObject
{
public:
	Object(Vector2f _position, string _strTexturePath, weak_ptr<b2World> _sceneWorld, bool _bIsStatic = false);
	~Object();

	// Position Methods
	void SetPosition(Vector2f _newPosition) override;
	void AddPosition(Vector2f _displacement) override;
	virtual Vector2f GetPosition() override;

	// Physics Methods
	void ApplyForce(Vector2f _force);

	// Texture Methods
	void SetTexture(string _strTexturePath);
	const sf::Texture* GetTexture() const;

	// Render Methods
	virtual void Render(sf::RenderTexture* _sceneBuffer) override;

private:
	sf::Sprite m_sprite;

	weak_ptr<b2World> m_world;
	b2Body* m_body;
};