#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager() :
	m_SoundBuffers(),
	m_SoundPool(),
	m_Loop(false)
{
	// Initial Capacity
	m_SoundPool = std::vector<sf::Sound>(20);
	std::fill(m_SoundPool.begin(), m_SoundPool.begin(), sf::Sound());
}

void SoundManager::LoadSoundBuffers()
{
	for (auto& Map : m_SoundMap)
	{
		m_SoundBuffers.emplace(std::make_pair(Map.first, sf::SoundBuffer()));
		// Check Loading
		if (!m_SoundBuffers[Map.first].loadFromFile(Map.second))
		{
			std::cout << "File Did Not Load = " << Map.second << std::endl;
		}
	}
}

void SoundManager::PlaySound(SoundType Type)
{
	// Find an Sound to Play
	for (auto& Sound : m_SoundPool)
	{
		if (Sound.getStatus() != sf::Sound::Playing)
		{
			Sound.setBuffer(m_SoundBuffers.at(Type));
			Sound.play();
			return;
		}
	}
}

void SoundManager::SetLoop(SoundType Type, bool Loop)
{
	// Find the Sound to Loop
	for (auto& Sound : m_SoundPool)
	{
		if (Sound.getStatus() != sf::Sound::Playing)
		{
			Sound.setBuffer(m_SoundBuffers.at(Type));
			Sound.setLoop(Loop);
			return;
		}
	}
}