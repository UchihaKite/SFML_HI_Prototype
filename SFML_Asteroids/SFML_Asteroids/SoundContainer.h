#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>

class SoundContainer
{
public:
	SoundContainer();
	static sf::Sound& GetSound(std::string const& FileName);
	static void Clear(); // Clears the Contents of the "std::map"s
private:
	/*
	Map Container that holds Pairs
	Pairs = Strings(Key) and Sounds(What's Returned)
	*/
	std::map<std::string, sf::Sound> m_Sounds;

	// Pairs = Strings(Key) and SoundBuffers(What's Returned)
	std::map<std::string, sf::SoundBuffer> m_Buffers;

	// A Pointer of the Same Type as the Class
	// One and Only Instance of this Class
	static SoundContainer* m_s_Instance;
	int m_NumberOfSoundsCreated;
	int m_NumberOfBuffersCreated;
};