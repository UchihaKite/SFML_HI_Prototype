#include "SoundContainer.h"
#include <iostream>

// For the "Assert" Function
#include <assert.h>

// Initialize the Pointer as a "NULL" Pointer
SoundContainer* SoundContainer::m_s_Instance = nullptr;

SoundContainer::SoundContainer() :
	m_NumberOfBuffersCreated(0),
	m_NumberOfSoundsCreated(0)
{
	assert(m_s_Instance == nullptr); // Assures the Pointer is Initially "NULL"
	m_s_Instance = this; // Stores the First Instance of the Class
}

sf::Sound& SoundContainer::GetSound(std::string const& FileName)
{
	// Get a Reference to "m_Sounds/m_Buffers" using our Instance
	auto& S = m_s_Instance->m_Sounds;
	auto& B = m_s_Instance->m_Buffers;
	// Auto is the equivalent of "std::map<std::string, sf::Sound>"
	// and "std::map<std::string, sf::SoundBuffer>"

	// Create an Iterator to hold the key-value-pair (kvp)
	// and search for the required kvp using the "FileName"
	auto KeyValuePair = S.find(FileName);
	// Auto is the equivalent of "std::map<std::string, sf::Sound>::iterator"

	// Did it Find a Match?
	if (KeyValuePair != S.end())
	{
		m_s_Instance->m_NumberOfSoundsCreated++;
		std::cout << m_s_Instance->m_NumberOfSoundsCreated << std::endl;
		// Yes, Return the Sound
		return KeyValuePair->second;
		// The Second part of the kvp, the "sf::Sound"
	}
	else
	{
		// No, Create a New kvp using the FileName
		auto& tempBuffer = B[FileName];
		if (!tempBuffer.loadFromFile(FileName))
		{
			std::cout << "File did not load!" << std::endl;
		}

		auto& Sound = S[FileName];
		// Load the Sound the Usual Way
		Sound.setBuffer(tempBuffer);

		// Return the Sound to the Calling Code
		return Sound;
	}
}

void SoundContainer::Clear()
{
	m_s_Instance->m_Sounds.clear();
	m_s_Instance->m_Buffers.clear();
}