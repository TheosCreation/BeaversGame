#include "Slider.h"

typedef unsigned int uint;

/*
	Creates a Slider Object

	@author Jamuel Bocacao
	@param Vector2f: Position of Slider
	@param unsigned int: Initial value of Slider
	@param unsigned int: Max Value of Slider
	@param shared_ptr<Event<void, int>>: Event that is executed during Slider Drag Event
*/
Slider::Slider(Vector2f _position, unsigned int _iValue, unsigned int _iMaxValue, shared_ptr<Event<void, int>> _dragEvent)
{
	// Create Slider Game Objects
	m_sliderBar = make_unique<Image>(_position, "Resources/Images/Slider/Bar.png");
	m_sliderHandle = make_unique<Image>(_position, "Resources/Images/Slider/Handle.png");

	// Set Slider Properties
	m_iValue = _iValue;
	m_iMaxValue = _iMaxValue;
	m_iSliderWidth = m_sliderBar->GetTexture()->getSize().x;
	m_dragEvent = _dragEvent;

	// Set Handle Position
	float fHandlePosX = m_iSliderWidth * ((_iValue / _iMaxValue) - 0.5f);
	Vector2f handlePos(fHandlePosX, 0.0f);
	m_sliderHandle->AddPosition(handlePos);
}

/*
	Sets Position of Slider

	@author Jamuel Bocacao
	@param Vector2f: New Position of Slider
*/
void Slider::SetPosition(Vector2f _newPosition)
{
	m_sliderBar->SetPosition(_newPosition);
	m_sliderHandle->SetPosition(_newPosition);

	float fHandlePosX = m_sliderBar->GetTexture()->getSize().x * ((m_iValue / m_iMaxValue) - 0.5f);
	Vector2f handlePos(fHandlePosX, 0.0f);

	m_sliderHandle->AddPosition(handlePos);
}

/*
	Displaces Slider Position

	@author Jamuel Bocacao
	@param Vector2f: Displacement Vector
*/
void Slider::AddPosition(Vector2f _displacement)
{
	m_sliderBar->AddPosition(_displacement);
	m_sliderHandle->AddPosition(_displacement);
}

/*
	Gets Position of Slider

	@author Jamuel Bocacao
	@return Vector2f: Position of Slider
*/
Vector2f Slider::GetPosition()
{
	return m_sliderBar->GetPosition();
}

/*
	Renders Slider to Scene's View Buffer

	@author Jamuel Bocacao
	@param sf::RenderTexture*: Scene's View Buffer
*/
void Slider::Render(sf::RenderTexture* _sceneBuffer)
{
	if (m_bIsActive && m_bIsVisible)
	{
		m_sliderBar->Render(_sceneBuffer);
		m_sliderHandle->Render(_sceneBuffer);
	}
}

/*
	Handles Slider's Click Event
	Begins Slider Dragging

	@author Jamuel Bocacao
	@param Vector2f: Mouse Position in World-Space
*/
void Slider::OnClick(Vector2f _mousePos)
{
	auto barObjectRect = m_sliderBar->GetBounds();
	auto handleObjectRect = m_sliderHandle->GetBounds();
	
	if (barObjectRect.contains(Vector2f(_mousePos)) || handleObjectRect.contains(Vector2f(_mousePos)))
	{
		m_bIsDragging = true;
	}
}

/*
	Handles Slider's Drag Event
	Updates Handle Position and Slider's Value

	@author Jamuel Bocacao
	@param Vector2f: Mouse Position in World-Space
*/
void Slider::OnDrag(Vector2f _mousePos)
{
	// Check if slider handle is being dragged
	if (!m_bIsDragging) return;

	// Get Mouse Position in World-Space
	float fHorizontalDisplacement = _mousePos.x - GetPosition().x;

	// Clamp to Slider Region
	if (abs(fHorizontalDisplacement) > (m_iSliderWidth / 2.0f))
	{
		fHorizontalDisplacement = (m_iSliderWidth / 2.0f) * ((fHorizontalDisplacement < 0) ? -1 : 1);
	}

	// Set new handle position
	auto handlePosition = GetPosition();
	handlePosition.x += fHorizontalDisplacement;
	m_sliderHandle->SetPosition(handlePosition);

	// Set new value
	m_iValue = uint(((fHorizontalDisplacement + m_iSliderWidth / 2.0f) / m_iSliderWidth) * m_iMaxValue);
	m_dragEvent->execute(m_iValue);
}

/*
	Handles Slider's Release Event
	Stops Slider Dragging

	@author Jamuel Bocacao
	@param Vector2f: Mouse Position in World-Space
*/
void Slider::OnRelease(Vector2f _mousePos)
{
	m_bIsDragging = false;
}
