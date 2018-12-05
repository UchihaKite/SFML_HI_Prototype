#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager() :
	m_Textures()
{
}

void TextureManager::LoadTextures()
{
	for (auto& Map : m_TextureMap)
	{
		m_Textures.emplace(std::make_pair(Map.first, sf::Texture()));
		// Check Loading
		if (!m_Textures[Map.first].loadFromFile(Map.second))
		{
			std::cout << "File Did Not Load = " << Map.second << std::endl;
		}
	}
}

sf::Texture& TextureManager::ReturnTexture(TextureType Type)
{
	// Find an Texture to Return
	for (auto& Texture : m_Textures)
	{
		if (Texture.first == Type)
		{
			return Texture.second;
		}
	}
}