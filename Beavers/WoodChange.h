#pragma once
#include "Image.h"
#include "Text.h"

class WoodChange : public GameObject
{
public:
	WoodChange(Vec2f _spawnPosition, int _iAmount);

	void SetPosition(Vec2f _newPosition) override;
	void AddPosition(Vec2f _displacement) override;
	Vec2f GetPosition() override;

	void Render(sf::RenderTexture* _sceneBuffer) override;

	void Update(float _fDeltaTime) override;

private:
	unique_ptr<Image> m_woodItemIcon;
	unique_ptr<Text> m_woodAmountText;

	sf::Clock m_despawnClock;
};

