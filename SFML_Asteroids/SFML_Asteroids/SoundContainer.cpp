#include "SoundContainer.h"
#include <iostream>

SoundContainer::SoundContainer()
{
	m_Sounds = std::map<std::string, sf::Sound>();
	m_Buffers = std::map<std::string, sf::SoundBuffer>();
}

sf::Sound& SoundContainer::GetSound(std::string const& FileName)
{
	// Create an Iterator to hold the key-value-pair (kvp)
	// and search for the required kvp using the "FileName"
	auto KeyValuePair = m_Sounds.find(FileName);
	// Auto is the equivalent of "std::map<std::string, sf::Sound>::iterator"

	// Did it Find a Match?
	if (KeyValuePair != m_Sounds.end())
	{
		// Yes, Return the Sound
		return KeyValuePair->second;
		// The Second part of the kvp, the "sf::Sound"
	}
	else
	{
		// No, Create a New kvp using the FileName
		auto& tempBuffer = m_Buffers[FileName];
		if (!tempBuffer.loadFromFile(FileName))
		{
			std::cout << "File did not load!" << std::endl;
		}

		auto& Sound = m_Sounds[FileName];
		// Load the Sound the Usual Way
		Sound.setBuffer(tempBuffer);

		// Return the Sound to the Calling Code
		return Sound;
	}
}

void SoundContainer::Clear()
{
	m_Sounds.clear();
	m_Buffers.clear();
}