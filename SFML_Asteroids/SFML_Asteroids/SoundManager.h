#pragma once
#include <array>
#include <string>
#include <map>
#include <vector>
#include <SFML/Audio.hpp>

/*
Objects will no longer need
sf::Sound Member Variables
They only call SoundManager to Play a Sound
*/

enum SoundType
{
	BACKGROUND_SONG,
	PLAYER_SHOOTING,
	PLAYER_DYING,
	PLAYER_RESPAWN,
	GAMEOBJECT_EXPLOSION,
	COUNT
};

class SoundManager
{
public:
	SoundManager();

	void LoadSoundBuffers();
	void PlaySound(SoundType Type);
	void SetLoop(SoundType Type, bool Loop);
private:
	// Map Paths to Enum
	std::map<SoundType, std::string> m_SoundMap =
	{
		{BACKGROUND_SONG, "Game Assets/Audio/Song.wav"},
		{PLAYER_SHOOTING, "Game Assets/Audio/Shooting.wav"},
		{PLAYER_DYING, "Game Assets/Audio/Dying.wav"},
		{PLAYER_RESPAWN, "Game Assets/Audio/Respawn.wav"},
		{GAMEOBJECT_EXPLOSION, "Game Assets/Audio/BlowUp.wav"}
	};

	std::map<SoundType, sf::SoundBuffer> m_SoundBuffers;
	std::vector<sf::Sound> m_SoundPool;
	bool m_Loop;
};