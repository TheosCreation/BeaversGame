#pragma once
#include "GameObject.h"

class Text : public GameObject
{
public:
	Text(Vec2f _position, string _strText, string _strFontPath);

	void SetText(string _strText);
	void SetFont(string _strFontPath);
	void SetSize(unsigned int _iFontSize);
	void SetColour(sf::Color _color);

	virtual void SetPosition(Vec2f _newPosition) override;
	virtual void AddPosition(Vec2f _displacement) override;
	virtual Vec2f GetPosition() override;

	void Render(sf::RenderTexture* _sceneBuffer) override;

private:
	sf::Text m_text;
	bool m_bUpdateText = false;
};

