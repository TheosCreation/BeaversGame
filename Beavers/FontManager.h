#pragma once
#include "Utils.h"

class FontManager
{
public:
	static FontManager& GetInstance();

	weak_ptr<sf::Font> GetFontRef(string _strFontPath);
	sf::Font& GetFont(string _strFontPath);
	void UnloadFont(string _strFontID);

	void UnloadAllFonts();

private:
	FontManager() = default;
	~FontManager() = default;

	FontManager(const FontManager& _copy) = delete;
	FontManager& operator = (const FontManager& _copy) = delete;

private:
	static FontManager m_instance;
	map<size_t, shared_ptr<sf::Font>> m_fonts;
};

inline FontManager FontManager::m_instance;
