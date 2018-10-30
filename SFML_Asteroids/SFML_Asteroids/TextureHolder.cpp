#include "TextureHolder.h"

// Include to use "assert()"
#include <assert.h>
#include <iostream>

// Initialize as Null
TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(m_s_Instance == nullptr); // Make sure "m_s_Instance" is Null
	m_s_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& FileName)
{
	/*
	Initialize a Reference to the Member Variable "m_Textures"
	Typically wouldn't use "auto", however, considering their is no chance the
	variable type would be anything other than "sf::Texture", figured it'd save
	me a little time typing it all out
	*/

	auto& M = m_s_Instance->m_Textures;
	// "auto" is the equivalent of "map<string,texture>"

	/*
	Create an iterator to hold a key value pair (kvp)
	and search for the required kvp using the passed in filename
	*/
	auto KeyValuePair = M.find(FileName);
	// "auto" is equivelant of "map<string,texture>::iterator"

	// Check to see if a Match was Found
	if (KeyValuePair != M.end())
	{
		// If True, Return the Texture
		return KeyValuePair->second;
	}
	else
	{
		// Filename Not Found
		// Create a New KVP using the FileName
		auto& Texture = M[FileName];
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
	m_s_Instance->m_Textures.clear();
}