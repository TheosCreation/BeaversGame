#pragma once
#include "GameObject.h"

class Image : public GameObject
{
public:
	Image(string _strTexturePath);
	Image(Vec2f _position, string _strTexturePath);

	void SetPosition(Vec2f _newPosition) override final;
	void AddPosition(Vec2f _displacement) override final;
	Vec2f GetPosition() override final;

	void SetTexture(string _strTexturePath);
	const sf::Texture* GetTexture() const;
	sf::FloatRect GetBounds();
	void SetScale(float x, float y) { m_sprite.setScale(x, y);};

	virtual void Render(sf::RenderTexture* _sceneBuffer) override;

protected:
	sf::Sprite m_sprite;
};

