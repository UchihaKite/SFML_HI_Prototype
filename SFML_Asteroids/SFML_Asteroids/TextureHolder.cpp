#include "TextureHolder.h"
#include <iostream>

TextureHolder::TextureHolder()
{
	m_Textures = std::map<std::string, sf::Texture>();
}

sf::Texture& TextureHolder::GetTexture(std::string const& FileName)
{
	/*
	Create an iterator to hold a key value pair (kvp)
	and search for the required kvp using the passed in filename
	*/
	auto KeyValuePair = m_Textures.find(FileName);
	// "auto" is equivelant of "map<string,texture>::iterator"

	// Check to see if a Match was Found
	if (KeyValuePair != m_Textures.end())
	{
		// If True, Return the Texture
		return KeyValuePair->second;
	}
	else
	{
		// Filename Not Found
		// Create a New KVP using the FileName
		auto& Texture = m_Textures[FileName];
		// "auto" is equivelant of "sf::Texture"

		// Load the Texture from File in Usual Way
		if (!Texture.loadFromFile(FileName))
		{
			std::cout << "You got the Filename wrong dummy" << std::endl;
		}
		// Return the Texture to the Calling Code
		return Texture;
	}
}

void TextureHolder::Clear()
{
	m_Textures.clear();
}