#pragma once
#include "Image.h"
#include "Event.h"

class Button : public Image
{
public:
	Button(string _strTexturePath, string _strSoundPath, shared_ptr<Event<void, void>> _event);
	Button(Vec2f _position, string _strTexturePath, string _strSoundPath, shared_ptr<Event<void, void>> _event);

	virtual void OnClick(Vec2f _mousePos) override;

	virtual void Render(sf::RenderTexture* _sceneBuffer) override;

private:
	shared_ptr<Event<void, void>> m_clickEvent;
	string m_strSoundID;
};