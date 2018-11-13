#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>

class TextureHolder
{
public:
	TextureHolder();

	static sf::Texture& GetTexture(std::string const& FileName);
	static void Clear(); // Clears the Contents of the "std::map"
private:
	/*
	A Map Container from STL
	Holds Related Pairs of String and Texture
	*/
	std::map<std::string, sf::Texture> m_Textures;

	/*
	A Pointer, Same Type of the Class Itself
	The One and Only Instance
	*/
	static TextureHolder* m_s_Instance;
};