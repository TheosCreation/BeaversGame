#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

using std::string;
using std::map;
using std::shared_ptr;
using std::weak_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_unique;

class TextureManager
{
public:
	static TextureManager& GetInstance();

	weak_ptr<sf::Texture> GetTexture(string _strTexPath);
	void UnloadTexture(string _strTextureID);

	void UnloadAllTextures();

private:
	TextureManager() = default;
	~TextureManager() = default;

	TextureManager(const TextureManager& _copy) = delete;
	TextureManager& operator = (const TextureManager& _copy) = delete;

private:
	static TextureManager m_instance;
	map<size_t, shared_ptr<sf::Texture>> m_textures;
};

inline TextureManager TextureManager::m_instance;