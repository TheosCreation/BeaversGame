#pragma once
#include "Image.h"
#include "Event.h"

class Slider : public GameObject
{
public:
	Slider(Vector2f _position, unsigned int _iValue, unsigned int _iMaxValue, shared_ptr<Event<void, int>> _dragEvent);

	// Position Methods
	virtual void SetPosition(Vector2f _newPosition) override;
	virtual void AddPosition(Vector2f _displacement) override;
	virtual Vector2f GetPosition() override;

	// Render Methods
	virtual void Render(sf::RenderTexture* _sceneBuffer) override;

	// Mouse Methods
	virtual void OnClick(Vector2f _mousePos) override;
	virtual void OnDrag(Vector2f _mousePos) override;
	virtual void OnRelease(Vector2f _mousePos) override;

private:
	unique_ptr<Image> m_sliderBar;
	unique_ptr<Image> m_sliderHandle;

	unsigned int m_iValue;
	unsigned int m_iMaxValue;
	unsigned int m_iSliderWidth;

	bool m_bIsDragging = false;

	shared_ptr<Event<void, int>> m_dragEvent;
};

