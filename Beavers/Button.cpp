#include "Button.h"
#include "AudioManager.h"

/*
	Creates a Button
	
	@author Jamuel Bocacao
	@param string: Texture File Path
	@param string: Click Sound File Path
	@param shared_ptr<Event<void, void>>: Event to be executed on click
*/
Button::Button(string _strTexturePath, string _strSoundPath, shared_ptr<Event<void, void>> _event) : Image(_strTexturePath)
{
	m_clickEvent = _event;
	m_strSoundID = _strSoundPath;
}

/*
	Creates a Button

	@author Jamuel Bocacao
	@param Vec2f: Position of Button
	@param string: Texture File Path
	@param string: Click Sound File Path
	@param shared_ptr<Event<void, void>>: Event to be executed on click
*/
Button::Button(Vec2f _position, string _strTexturePath, string _strSoundPath, shared_ptr < Event<void, void>> _event) : Image(_position, _strTexturePath)
{
	m_clickEvent = _event;
	m_strSoundID = _strSoundPath;
}

/*
	Handles Button's Click Event
	Executes Event

	@author Jamuel Bocacao
	@param Vec2f: Mouse Position in World-Space
	@return bool: Successfully clicked on Button
*/
bool Button::OnClick(Vec2f _mousePos)
{
	auto objectBounds = m_sprite.getGlobalBounds();
	
	if (objectBounds.contains(_mousePos))
	{
		m_clickEvent->execute();
		AudioManager::GetInstance().PlaySound(m_strSoundID);
		return true;
	}
	return false;
}
