#include "FontManager.h"

/*
	Gets the Font Manager's Instance

	@author Jamuel Bocacao
	@return FontManager&: FontManager Instance
*/
FontManager& FontManager::GetInstance()
{
	return m_instance;
}

/*
	Gets a Font Reference based on ID or Font File Path

	@author Jamuel Bocacao
	@param string: Font ID or File Path
	@return weak_ptr<sf::Font>: Reference to Font
*/
weak_ptr<sf::Font> FontManager::GetFontRef(string _strFontPath)
{
	// Generate a Hash ID based on Font path
	std::hash<string> hashGenerator;
	size_t fontID = hashGenerator(_strFontPath);

	// Check if Font has already been loaded
	if (!m_fonts.contains(fontID))
	{
		// If not load Font file
		auto font = make_shared<sf::Font>();
		font->setSmooth(true);
		if (font->loadFromFile(_strFontPath))
		{
			// Store Font using path as File ID
			m_fonts.emplace(fontID, font);
			return font;
		}
		else
		{
			printf("Missing Font: \"%s\"", _strFontPath.c_str());
			return weak_ptr<sf::Font>();
		}
	}

	// Return existing Font
	return m_fonts.at(fontID);
}

/*
	Gets a Font based on ID or Font File Path

	@author Jamuel Bocacao
	@param string: Font ID or File Path
	@return sf::Font&: Font
*/
sf::Font& FontManager::GetFont(string _strFontPath)
{
	// Generate a Hash ID based on Font path
	std::hash<string> hashGenerator;
	size_t fontID = hashGenerator(_strFontPath);

	// Check if Font has already been loaded
	if (!m_fonts.contains(fontID))
	{
		// If not load Font file
		auto font = make_shared<sf::Font>();
		font->setSmooth(true);
		if (font->loadFromFile(_strFontPath))
		{
			// Store Font using path as File ID
			m_fonts.emplace(fontID, font);
			return *font.get();
		}
		else
		{
			printf("Missing Font: \"%s\"", _strFontPath.c_str());
			sf::Font missingFont;
			return *font.get();
		}
	}

	// Return existing Font
	return *m_fonts.at(fontID).get();
}

/*
	Removes Font from Font Manager

	@author Jamuel Bocacao
	@param string: Font ID
*/
void FontManager::UnloadFont(string _strFontPath)
{
	// Generate a Hash ID based on Font path
	std::hash<std::string> hashGenerator;
	size_t FontID = hashGenerator(_strFontPath);

	// Check if Font exists from the ID
	if (m_fonts.count(FontID) > 0)
	{
		// Erase Font
		m_fonts.erase(FontID);
	}
}

/*
	Unloads all Fonts from Font Manager

	@author Jamuel Bocacao
	@param string: Font ID
*/
void FontManager::UnloadAllFonts()
{
	m_fonts.clear();
}
