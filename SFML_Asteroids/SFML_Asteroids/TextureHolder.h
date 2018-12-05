#pragma once
#include "SoundContainer.h"

/*
THIS IS NO LONGER BEING USED
JUST KEEPING THIS HERE TO REFER
BACK TO
*/

class TextureHolder
{
public:
	TextureHolder();

	sf::Texture& GetTexture(std::string const& FileName);
	void Clear(); // Clears the Contents of the "std::map"
private:
	/*
	A Map Container from STL
	Holds Related Pairs of String and Texture
	*/
	std::map<std::string, sf::Texture> m_Textures;
};