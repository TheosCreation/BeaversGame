#pragma once
#include "Image.h"
#include "Event.h"

class Slider : public GameObject
{
public:
	Slider(Vec2f _position, unsigned int _iValue, unsigned int _iMaxValue, shared_ptr<Event<void, int>> _dragEvent);

	// Position Methods
	virtual void SetPosition(Vec2f _newPosition) override;
	virtual void AddPosition(Vec2f _displacement) override;
	virtual Vec2f GetPosition() override;

	// Render Methods
	virtual void Render(sf::RenderTexture* _sceneBuffer) override;

	// Mouse Methods
	virtual bool OnClick(Vec2f _mousePos) override;
	virtual void OnDrag(Vec2f _mousePos) override;
	virtual void OnRelease(Vec2f _mousePos) override;

private:
	unique_ptr<Image> m_sliderBar;
	unique_ptr<Image> m_sliderHandle;

	unsigned int m_iValue;
	unsigned int m_iMaxValue;
	unsigned int m_iSliderWidth;

	bool m_bIsDragging = false;

	shared_ptr<Event<void, int>> m_dragEvent;
};

