#include "WoodChange.h"

WoodChange::WoodChange(Vec2f _spawnPosition, int _iAmount)
{
	m_woodItemIcon = make_unique<Image>(_spawnPosition, "Resources/Images/WoodItem.png");
	m_woodAmountText = make_unique<Text>(_spawnPosition + Vec2f(20.0f, -2.0f), ((_iAmount > 0) ? "+" : "") + std::to_string(_iAmount), "Resources/Fonts/Yogurt Extra.ttf");
	m_woodAmountText->SetColour((_iAmount < 0) ? sf::Color::Red : sf::Color::Green);
	m_woodAmountText->SetSize(12);
	m_despawnClock.restart();
}

void WoodChange::SetPosition(Vec2f _newPosition)
{
	m_woodItemIcon->SetPosition(_newPosition);
	m_woodAmountText->SetPosition(_newPosition + Vec2f(45.0f, 0.0f));
}

void WoodChange::AddPosition(Vec2f _displacement)
{
	m_woodAmountText->AddPosition(_displacement);
	m_woodItemIcon->AddPosition(_displacement);
}

Vec2f WoodChange::GetPosition()
{
	return m_woodItemIcon->GetPosition();
}

void WoodChange::Render(sf::RenderTexture* _sceneBuffer)
{
	m_woodItemIcon->Render(_sceneBuffer);
	m_woodAmountText->Render(_sceneBuffer);
}

void WoodChange::Update(float _fDeltaTime)
{
	if (m_despawnClock.getElapsedTime().asSeconds() > 1.0f)
	{
		Destroy();
		return;
	}
	AddPosition(Vec2f(0.0f, -32.0f) * _fDeltaTime);
}
