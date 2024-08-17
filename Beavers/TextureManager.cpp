#include "TextureManager.h"

/*
	Gets the Texture Manager's Instance

	@author Jamuel Bocacao
	@return TextureManager&: TextureManager Instance
*/
TextureManager& TextureManager::GetInstance()
{
	return m_instance;
}

/*
	Gets a Texture Reference based on ID or Texture File Path

	@author Jamuel Bocacao
	@param string: Texture ID or File Path
	@return weak_ptr<sf::Texture>: Reference to Texture
*/
weak_ptr<sf::Texture> TextureManager::GetTextureRef(string _strTexPath)
{
	// Generate a Hash ID based on texture path
	std::hash<string> hashGenerator;
	size_t textureID = hashGenerator(_strTexPath);

	// Check if Texture has already been loaded
	if (!m_textures.contains(textureID))
	{
		// If not load texture file
		auto texture = make_shared<sf::Texture>();
		texture->setSmooth(true);
		if (texture->loadFromFile(_strTexPath))
		{
			// Store Texture using path as File ID
			m_textures.emplace(textureID, texture);
			return texture;
		}
		else
		{
			printf("Missing Texture: \"%s\"", _strTexPath.c_str());
			return weak_ptr<sf::Texture>();
		}
	}

	// Return existing Texture
	return m_textures.at(textureID);
}

/*
	Gets a Texture based on ID or Texture File Path

	@author Jamuel Bocacao
	@param string: Texture ID or File Path
	@return sf::Texture&: Texture
*/
sf::Texture& TextureManager::GetTexture(string _strTexPath)
{
	// Generate a Hash ID based on texture path
	std::hash<string> hashGenerator;
	size_t textureID = hashGenerator(_strTexPath);

	// Check if Texture has already been loaded
	if (!m_textures.contains(textureID))
	{
		// If not load texture file
		auto texture = make_shared<sf::Texture>();
		texture->setSmooth(true);
		if (texture->loadFromFile(_strTexPath))
		{
			// Store Texture using path as File ID
			m_textures.emplace(textureID, texture);
			return *texture.get();
		}
		else
		{
			printf("Missing Texture: \"%s\"", _strTexPath.c_str());
			sf::Texture missingTexture;
			return missingTexture;
		}
	}

	// Return existing Texture
	return *m_textures.at(textureID).get();
}

/*
	Removes Texture from Texture Manager

	@author Jamuel Bocacao
	@param string: Texture ID
*/
void TextureManager::UnloadTexture(string _strTexturePath)
{
	// Generate a Hash ID based on texture path
	std::hash<std::string> hashGenerator;
	size_t textureID = hashGenerator(_strTexturePath);

	// Check if Texture exists from the ID
	if (m_textures.count(textureID) > 0)
	{
		// Erase Texture
		m_textures.erase(textureID);
	}
}

/*
	Unloads all Textures from Texture Manager

	@author Jamuel Bocacao
	@param string: Texture ID
*/
void TextureManager::UnloadAllTextures()
{
	m_textures.clear();
}
